
#include "Player/STUPlayerCharacter.h"
#include "STUWeaponComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ASTUPlayerCharacter::ASTUPlayerCharacter(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(GetRootComponent());
    CameraBoom->bUsePawnControlRotation = true;
    CameraBoom->TargetArmLength = 300.f;
    CameraBoom->SocketOffset = FVector(0.f, 70.f, 200.f);
    
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraFollow"));
    FollowCamera->SetupAttachment(CameraBoom);

    WalkSpeed = 600.f;
    SprintSpeed = 900.f;
}

void ASTUPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
    SetMovementStatus(EMovementStatus::EMS_Normal);
}

void ASTUPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent)
    check(WeaponComponent)
    
    PlayerInputComponent->BindAxis("MoveForward", this, &ASTUPlayerCharacter::MoveForward);   
    PlayerInputComponent->BindAxis("MoveRight", this, &ASTUPlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &APawn::AddControllerYawInput);
    
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASTUPlayerCharacter::Sprint);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASTUPlayerCharacter::StopSprinting);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTUWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUWeaponComponent::StopFire);
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USTUWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTUWeaponComponent::Reload);
}

void ASTUPlayerCharacter::MoveForward(float Amount)
{
    if(!Amount) return;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTUPlayerCharacter::MoveRight(float Amount)
{
    if(!Amount) return;
    AddMovementInput(GetActorRightVector(), Amount);
}

void ASTUPlayerCharacter::Sprint()
{
    SetMovementStatus(EMovementStatus::EMS_Sprint);
}

void ASTUPlayerCharacter::StopSprinting()
{
    SetMovementStatus(EMovementStatus::EMS_Normal);
}

void ASTUPlayerCharacter::SetMovementStatus(const EMovementStatus Status)
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

void ASTUPlayerCharacter::OnDeath()
{
    Super::OnDeath();
    if(Controller) GetController()->ChangeState(NAME_Spectating);
}