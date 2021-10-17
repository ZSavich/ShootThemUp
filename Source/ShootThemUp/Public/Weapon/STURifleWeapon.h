// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;

UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

public:
    ASTURifleWeapon();

    virtual void BeginPlay() override;
    virtual void StartFire() override;
    virtual void StopFire() override;
    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector& StartPoint, FVector& EndPoint) const override;
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSettings")
    float FireRate;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSettings")
    float FireScatter;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSettings")
    float DamageAmount;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FX")
    USTUWeaponFXComponent* WeaponFX;
    
private:
    FTimerHandle FireTimer;
    
    void MakeDamage(AActor* const TargetActor);
};
