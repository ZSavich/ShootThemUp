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

void ASTULauncherWeapon::StopFire()
{
    
}

void ASTULauncherWeapon::MakeShot()
{
    const FTransform ProjectileSpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    const auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass,ProjectileSpawnTransform);

    UGameplayStatics::FinishSpawningActor(Projectile, ProjectileSpawnTransform);
}

