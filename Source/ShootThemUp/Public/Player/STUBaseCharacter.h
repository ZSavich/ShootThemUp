// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

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
	// Sets default values for this character's properties
	ASTUBaseCharacter();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USpringArmComponent* CameraBoom;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCameraComponent* FollowCamera;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Customize Movement")
    EMovementStatus MovementStatus;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customize Movement")
    float WalkSpeed = 600.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customize Movement")
    float SprintSpeed;
    
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintPure)
    float GetMovementDirection();

private:
    void MoveForward(float Amount);
    void MoveRight(float Amount);

    void Sprint();
    void StopSprinting();

    void SetMovementStatus(const EMovementStatus Status);
};
