// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUCoreTypes.h"
#include "STUBaseCharacter.generated.h"

class USTUHealthComponent;
class USTUWeaponComponent;
class USTUEquipFinishedNotify;
class USoundCue;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASTUBaseCharacter(const FObjectInitializer& ObjectInitializer);
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
    TMap<UPhysicalMaterial*,float> DamageModifier;
    
    UFUNCTION(BlueprintPure)
    float GetMovementDirection() const;
    
    void SetPlayerColor(const FLinearColor& Color) const;
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USTUHealthComponent*  HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USTUWeaponComponent* WeaponComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sounds")
    USoundCue* DeathSound;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    EMovementStatus MovementStatus;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    FVector2D LandedDamageVelocity; 

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    FVector2D LandedDamage;
    
    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    UAnimMontage* DeathMontage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Death")
    float LifeSpan;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game")
    FName MaterialColorName;
    
    virtual void OnHealthChanged(const float Health, const float HealthDelta);
	virtual void BeginPlay() override;
    virtual void OnDeath();
private:
    UFUNCTION()
    void OnGroundLanded(const FHitResult& HitResult);

};
