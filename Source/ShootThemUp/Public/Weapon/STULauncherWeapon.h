// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STULauncherWeapon.generated.h"

class ASTUProjectile;

UCLASS()
class SHOOTTHEMUP_API ASTULauncherWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

public:
    ASTULauncherWeapon();
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSettings | Projectile")
    TSubclassOf<ASTUProjectile> ProjectileClass;

    virtual void StartFire() override;
    virtual void MakeShot() override;

protected:
    virtual void BeginPlay() override;
};
