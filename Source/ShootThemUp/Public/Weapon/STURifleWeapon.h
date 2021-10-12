// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"


UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

public:
    ASTURifleWeapon();
    
    virtual void StartFire() override;
    virtual void StopFire() override;
    virtual void MakeShot() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSettings")
    float FireRate;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSettings")
    float FireScatter;
    
private:
    FTimerHandle FireTimer;

    bool GetTraceData(FVector& StartPoint, FVector& EndPoint) const;
    void MakeHit(FHitResult& HitResult, const FVector& StartPoint, const FVector& EndPoint) const;
    void MakeDamage(AActor* const TargetActor);
};
