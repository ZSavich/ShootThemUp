// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;

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

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VFX")
    USTUWeaponFXComponent* WeaponFX;

    UPROPERTY()
    UNiagaraComponent* MuzzleEffectComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
    UNiagaraSystem* TraceEffect;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
    FName TraceTargetName;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UAudioComponent* ShootAudioComponent;
    
private:
    FTimerHandle FireTimer;
    
    void MakeDamage(AActor* const TargetActor);
    void InitFX();
    void SetFXVisible(const bool isActive) const;
    void SpawnTraceFX(const FVector StartTarget, const FVector EndTarget) const;
    AController* GetController() const;
};
