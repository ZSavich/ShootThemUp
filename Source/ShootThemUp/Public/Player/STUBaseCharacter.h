// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USTUHealthComponent;
class UTextRenderComponent;

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
    EMS_Normal   UMETA(DisplayName = "Normal"),
    EMS_Sprint   UMETA(DisplayName = "Sprint"),
 
    EMS_MAX      UMETA(DisplayName = "MaxDefault")
};
 

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
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USpringArmComponent* CameraBoom;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCameraComponent* FollowCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USTUHealthComponent*  HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UTextRenderComponent* HealthRenderText;
    
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
    void MoveForward(float Amount);
    void MoveRight(float Amount);

    void Sprint();
    void StopSprinting();

    void SetMovementStatus(const EMovementStatus Status);

    void OnDeath();
    void OnHealthChanged(const float Health);

    UFUNCTION()
    void OnGroundLended(const FHitResult& HitResult);
};
