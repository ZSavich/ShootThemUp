// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUCoreTypes.h"
#include "STUBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USTUHealthComponent;
class UTextRenderComponent;
class USTUWeaponComponent;
class USTUEquipFinishedNotify;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASTUBaseCharacter();
    
    virtual void Tick(float DeltaTime) override;
    
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintPure)
    float GetMovementDirection() const;

    //FORCEINLINE USTUHealthComponent* GetHealthComponent() const {return HealthComponent;}
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USpringArmComponent* CameraBoom;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCameraComponent* FollowCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USTUHealthComponent*  HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UTextRenderComponent* HealthRenderText;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Conponents")
    USTUWeaponComponent* WeaponComponent;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    EMovementStatus MovementStatus;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    FVector2D LandedDamageVelocity; 

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    FVector2D LandedDamage;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float WalkSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float SprintSpeed;
    
    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    UAnimMontage* DeathMontage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Death")
    float LifeSpan;
    
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    UFUNCTION()
    void OnGroundLanded(const FHitResult& HitResult);
    
    void MoveForward(float Amount);
    void MoveRight(float Amount);

    void Sprint();
    void StopSprinting();

    void SetMovementStatus(const EMovementStatus Status);

    void OnDeath();
    void OnHealthChanged(const float Health, const float HealthDelta) const;

};
