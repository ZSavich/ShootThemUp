// Shoot Them Up. All rights reserved.


#include "Player/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(GetRootComponent());
    CameraBoom->bUsePawnControlRotation = true;
    
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraFollow"));
    FollowCamera->SetupAttachment(CameraBoom);
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
    
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    if(PlayerInputComponent)
    {
        PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);   
        PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);
        PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
        PlayerInputComponent->BindAxis("TurnAround", this, &APawn::AddControllerYawInput);
        
        PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
        PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASTUBaseCharacter::Sprint);
        PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASTUBaseCharacter::StopSprinting);
    }
}

float ASTUBaseCharacter::GetMovementDirection()
{
    if(GetVelocity().IsZero()) return 0.f;
    
    const FVector VelocityNormalized = GetVelocity().GetSafeNormal();
    const FVector ForwardVector = GetActorForwardVector();
    const float DotProduct = FVector::DotProduct(VelocityNormalized, ForwardVector);
    const float VectorsAngle = FMath::RadiansToDegrees(FMath::Acos(DotProduct));
    const float CrossProductZSign = FMath::Sign(FVector::CrossProduct(VelocityNormalized, ForwardVector).Z); 
    
    return VectorsAngle * CrossProductZSign;
}

void ASTUBaseCharacter::MoveForward(float Amount)
{
    if(!Amount) return;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTUBaseCharacter::MoveRight(float Amount)
{
    if(!Amount) return;
    AddMovementInput(GetActorRightVector(), Amount);
}

void ASTUBaseCharacter::Sprint()
{
    SetMovementStatus(EMovementStatus::EMS_Sprint);
}

void ASTUBaseCharacter::StopSprinting()
{
    SetMovementStatus(EMovementStatus::EMS_Normal);
}

void ASTUBaseCharacter::SetMovementStatus(const EMovementStatus Status)
{
    switch(Status)
    {
        case EMovementStatus::EMS_Normal:
            MovementStatus = Status;
            GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
            break;
        case EMovementStatus::EMS_Sprint:
            MovementStatus = Status;
            GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
            break;
        case EMovementStatus::EMS_MAX:
            MovementStatus = Status;
            GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
            break;
        default:
            ;
    }
}