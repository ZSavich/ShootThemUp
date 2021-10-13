// Shoot Them Up. All rights reserved.


#include "Weapon/STULauncherWeapon.h"

#include "Kismet/GameplayStatics.h"
#include "Weapon/STUProjectile.h"

ASTULauncherWeapon::ASTULauncherWeapon()
{
    
}

void ASTULauncherWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(ProjectileClass);
}


void ASTULauncherWeapon::StartFire()
{
    MakeShot();
}

void ASTULauncherWeapon::MakeShot()
{
    if(!GetWorld() || IsAmmoEmpty()) return;

    FVector TraceStart, TraceEnd;
    if(!GetTraceData(TraceStart, TraceEnd)) return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();
    
    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    const auto Projectile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTransform);

    if(!Projectile) return;
    Projectile->SetShotDirection(Direction);
    Projectile->SetOwner(GetOwner());
    Projectile->FinishSpawning(SpawnTransform);
    DecreaseBullet();
}

