// Shoot Them Up. All rights reserved.


#include "STUHealthComponent.h"

#include "STUBaseCharacter.h"
#include "STUGameMode.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComp, All, Log);

USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

    MaxHealth = 100.f;

    bAutoHeal = true;
    HealUpdateTime = 0.5f;
    HealDelay = 3.f;
    HealModifier = 1.f;
}

bool USTUHealthComponent::TryToAddHealth(const float HealthAmount)
{
    if(Health == MaxHealth || IsDeath()) return false;

    SetHealth(FMath::Clamp(Health+HealthAmount, 0.f, MaxHealth));
    return true;
}


void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
    checkf(MaxHealth > 0, TEXT("Wrong USTUHealthComponent::MaxHealth parameter"));
    
    SetHealth(MaxHealth);
    AActor* OwnerActor = GetOwner();
    if(OwnerActor)
    {
        OwnerActor->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
        OwnerActor->OnTakePointDamage.AddDynamic(this, &USTUHealthComponent::OnTakePointDamage);
        OwnerActor->OnTakeRadialDamage.AddDynamic(this, &USTUHealthComponent::OnTakeRadialDamage);
    }
}

void USTUHealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation,
    UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
    const auto ModifiedDamage = Damage * GetPointDamageModifier(Damage,BoneName,InstigatedBy);
    
    ApplyDamage(ModifiedDamage, InstigatedBy);
}

void USTUHealthComponent::OnTakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin,
    FHitResult HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
    ApplyDamage(Damage, InstigatedBy);
}

void USTUHealthComponent::ApplyDamage(const float Damage, AController* InstigatedBy)
{
    if(Damage <= 0.f || IsDeath() || !GetWorld()) return;
    
    SetHealth(Health - Damage);
    PlayCameraShake();

    GetWorld()->GetTimerManager().ClearTimer(HealTimer);
    
    if(IsDeath())
    {
        Killed(InstigatedBy);
        OnDeath.Broadcast();
    }
    else if (bAutoHeal)
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimer, this,&USTUHealthComponent::HealUpdate,
          HealUpdateTime,true, HealDelay);  
    }
}

float USTUHealthComponent::GetPointDamageModifier(const float Damage, const FName BoneName, const AController* InstigatedBy) const
{
    const auto Instigator = Cast<ASTUBaseCharacter>(InstigatedBy->GetPawn());
    if(!Instigator) return 1.0;
    
    const auto BaseCharacter = GetOwner<ASTUBaseCharacter>();
    if(!BaseCharacter || BaseCharacter->DamageModifier.IsEmpty()) return 1.0;
    
    const auto PhysMaterial = BaseCharacter->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();
    if(!PhysMaterial && !BaseCharacter->DamageModifier.Contains(PhysMaterial)) return 1.0;
    
    return BaseCharacter->DamageModifier[PhysMaterial];
}

void USTUHealthComponent::HealUpdate()
{
    SetHealth(Health + HealModifier);
    
    if(FMath::IsNearlyEqual(Health,MaxHealth) && GetWorld()) GetWorld()->GetTimerManager().ClearTimer(HealTimer);
}

void USTUHealthComponent::SetHealth(float NewHealth)
{
    const auto ResultHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    const auto HealthDelta = ResultHealth - Health;
    Health = ResultHealth;
    OnHealthChanged.Broadcast(Health, HealthDelta);
}

void USTUHealthComponent::PlayCameraShake() const
{
    if(IsDeath() || !CameraShake) return;

    const auto Player = Cast<APawn>(GetOwner());
    if(!Player) return;

    const auto Controller = Cast<APlayerController>(Player->GetController());;
    if(!Controller || !Controller->PlayerCameraManager) return;

    Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

void USTUHealthComponent::Killed(AController* KillerController) const
{
    const auto GameMode = Cast<ASTUGameMode>(GetWorld()->GetAuthGameMode());
    const auto VictimPawn = Cast<APawn>(GetOwner());
    if(GameMode) GameMode->Killed(KillerController, VictimPawn->GetController());
}