// Shoot Them Up. All rights reserved.


#include "Weapon/STUProjectile.h"

#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    SphereComponent->InitSphereRadius(5.f);
    SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SphereComponent->SetCollisionResponseToAllChannels(ECR_Block);
    SphereComponent->IgnoreActorWhenMoving(GetOwner(), true);
    SetRootComponent(SphereComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    MovementComponent->InitialSpeed = 1500.f;
    MovementComponent->ProjectileGravityScale = 0.0f;

    DamageAmount = 45.f;
    DamageRadius = 100.f;
}

void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();
    check(MovementComponent);
    check(SphereComponent);

    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    SphereComponent->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnProjectileHit);
    
    SetLifeSpan(5.f);
}

void ASTUProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if(!GetWorld()) return;
    
    MovementComponent->StopMovementImmediately();

    UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(),DamageRadius,
        UDamageType::StaticClass(),{},this,GetController());

    DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24.f, FColor::Red,false,5.f);
    
    Destroy();
}

AController* ASTUProjectile::GetController() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    return Player ? Player->GetController() : nullptr;
}