// Shoot Them Up. All rights reserved.


#include "Weapon/STUProjectile.h"

#include "DrawDebugHelpers.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "STUWeaponFXComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PointLightComponent.h"

ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    SphereComponent->InitSphereRadius(5.f);
    SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SphereComponent->SetCollisionResponseToAllChannels(ECR_Block);
    SphereComponent->IgnoreActorWhenMoving(GetOwner(), true);
    SphereComponent->bReturnMaterialOnMove = true;
    SetRootComponent(SphereComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    MovementComponent->InitialSpeed = 1500.f;
    MovementComponent->ProjectileGravityScale = 0.0f;

    WeaponFX = CreateDefaultSubobject<USTUWeaponFXComponent>(TEXT("WeaponFXComponent"));

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    Mesh->SetupAttachment(GetRootComponent());

    TraceFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TraceEffect"));
    TraceFX->SetupAttachment(GetRootComponent());

    PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
    PointLight->SetupAttachment(GetRootComponent());

    ProjectileFlyAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("FlyAudio"));
    ProjectileFlyAudio->SetupAttachment(GetRootComponent());

    DamageAmount = 45.f;
    DamageRadius = 100.f;
}

void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();
    checkf(MovementComponent, TEXT("ASTUProjectile MovementComponent is Not Valid!"));
    checkf(SphereComponent, TEXT("ASTUProjectile SphereComponent is Not Valid!"));
    checkf(WeaponFX, TEXT("ASTUProjectile WeaponFX is Not Valid!"));
    checkf(ProjectileFlyAudio, TEXT("ASTUProjectile ProjectileFlyComponent is Not Valid!"))

    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    SphereComponent->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnProjectileHit);
    ProjectileFlyAudio->Activate();
    
    SetLifeSpan(5.f);
}

void ASTUProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if(!GetWorld()) return;
    
    MovementComponent->StopMovementImmediately();

    UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(),DamageRadius,
        UDamageType::StaticClass(),{},this,GetController());

    //DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24.f, FColor::Red,false,5.f);
    
    WeaponFX->PlayImpactFX(Hit);
    Mesh->DestroyComponent();
    PointLight->DestroyComponent();
    ProjectileFlyAudio->Deactivate();
    SetLifeSpan(2.f);
}

AController* ASTUProjectile::GetController() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    return Player ? Player->GetController() : nullptr;
}