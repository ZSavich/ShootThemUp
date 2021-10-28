// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUHealthComponent.generated.h"

class UCameraShakeBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUHealthComponent();
    
    FOnDeathSignature OnDeath;
    FOnHealthChangedSignature OnHealthChanged;

    bool TryToAddHealth(const float HealthAmount);

    FORCEINLINE float GetHealth() const {return Health;}
    FORCEINLINE bool IsDeath() const {return FMath::IsNearlyZero(Health);}
    
    UFUNCTION(BlueprintPure)
    FORCEINLINE float GetHealthPercent() const {return Health / MaxHealth;}

protected:
	virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health", meta = (ClampMin = "0"))
    float MaxHealth;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Heal")
    bool bAutoHeal;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Heal", meta = (ClampMin = "0", EditCondition = "bAutoHeal"))
    float HealUpdateTime;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Heal", meta = (ClampMin = "0", EditCondition = "bAutoHeal"))
    float HealDelay;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Heal", meta = (ClampMin = "0", EditCondition = "bAutoHeal"))
    float HealModifier;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
    TSubclassOf<UCameraShakeBase> CameraShake;
    
private:
    float Health;

    FTimerHandle HealTimer;
    
    UFUNCTION()
    void OnTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);
    UFUNCTION()
    void OnTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, FHitResult HitInfo, class AController* InstigatedBy, AActor* DamageCauser);

    void ApplyDamage(const float Damage, AController* InstigatedBy);
    void HealUpdate();
    void SetHealth(float NewHealth);
    void PlayCameraShake() const;
    void Killed(AController* KillerController) const;
    float GetPointDamageModifier(const float Damage, const FName BoneName, const AController* InstigatedBy) const;
};
