// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUCoreTypes.h"
#include "STUBaseCharacter.generated.h"

class USTUHealthComponent;
class USTUWeaponComponent;
class USTUEquipFinishedNotify;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASTUBaseCharacter(const FObjectInitializer& ObjectInitializer);
    
    UFUNCTION(BlueprintPure)
    float GetMovementDirection() const;
    
    void SetPlayerColor(const FLinearColor& Color) const;
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USTUHealthComponent*  HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Conponents")
    USTUWeaponComponent* WeaponComponent;
    
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
    
	virtual void BeginPlay() override;
    virtual void OnDeath();
private:
    UFUNCTION()
    void OnGroundLanded(const FHitResult& HitResult);
    void OnHealthChanged(const float Health, const float HealthDelta) const;

};
