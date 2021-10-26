
#include "Player/STUBaseCharacter.h"
#include "Components/STUHealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STUWeaponComponent.h"

ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

    HealthComponent = CreateDefaultSubobject<USTUHealthComponent>(TEXT("HealthComponent"));
    WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>(TEXT("WeaponComponent"));

    LandedDamageVelocity = FVector2D(900.f, 1600.f);
    LandedDamage = FVector2D(10.f, 100.f);

    LifeSpan = 5.f;

    MaterialColorName = "Paint Color";
}

void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

    check(HealthComponent);
    check(GetMovementComponent());

    OnHealthChanged(HealthComponent->GetHealth(), 0.f);
    HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);
    LandedDelegate.AddDynamic(this, &ASTUBaseCharacter::OnGroundLanded);
}

float ASTUBaseCharacter::GetMovementDirection() const
{
    if(GetVelocity().IsZero()) return 0.f;
    
    const FVector VelocityNormalized = GetVelocity().GetSafeNormal();
    const FVector ForwardVector = GetActorForwardVector();
    const float DotProduct = FVector::DotProduct(VelocityNormalized, ForwardVector);
    const float VectorsAngle = FMath::RadiansToDegrees(FMath::Acos(DotProduct));
    const float CrossProductZSign = FMath::Sign(FVector::CrossProduct(VelocityNormalized, ForwardVector).Z); 
    
    return VectorsAngle * CrossProductZSign;
}

void ASTUBaseCharacter::OnDeath()
{
    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);

    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
    SetLifeSpan(LifeSpan);
    WeaponComponent->StopFire();
}
void ASTUBaseCharacter::OnHealthChanged(const float Health, const float HealthDelta)
{}

void ASTUBaseCharacter::OnGroundLanded(const FHitResult& HitResult)
{
    const auto LandedVelocityZ = -GetVelocity().Z;
    
    if(LandedVelocityZ < LandedDamageVelocity.X) return;

    const auto FinalLandedDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity,
        LandedDamage, LandedVelocityZ);
    TakeDamage(FinalLandedDamage, FDamageEvent{},nullptr, nullptr);
}

void ASTUBaseCharacter::SetPlayerColor(const FLinearColor& Color) const
{
    const auto MaterialInstance = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
    if(!MaterialInstance) return;
    MaterialInstance->SetVectorParameterValue(MaterialColorName, Color);
}


