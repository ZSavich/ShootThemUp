
#include "Player/STUPlayerCharacter.h"
#include "STUWeaponComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ASTUPlayerCharacter::ASTUPlayerCharacter(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(GetRootComponent());
    CameraBoom->bUsePawnControlRotation = true;
    CameraBoom->TargetArmLength = 300.f;
    CameraBoom->SocketOffset = FVector(0.f, 70.f, 200.f);
    
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraFollow"));
    FollowCamera->SetupAttachment(CameraBoom);
    
    CameraCollision = CreateDefaultSubobject<USphereComponent>(TEXT("CameraCollision"));
    CameraCollision->SetupAttachment(FollowCamera);
    CameraCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
    
    WalkSpeed = 600.f;
    SprintSpeed = 900.f;
}

void ASTUPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
    SetMovementStatus(EMovementStatus::EMS_Normal);
    CameraCollision->OnComponentBeginOverlap.AddDynamic(this, &ASTUPlayerCharacter::OnCameraCollisionBeginOverlap);
    CameraCollision->OnComponentEndOverlap.AddDynamic(this, &ASTUPlayerCharacter::OnCameraCollisionEndOverlap);
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

    DECLARE_DELEGATE_OneParam(FZoomInputSignature, bool)
    PlayerInputComponent->BindAction<FZoomInputSignature>("Zoom", IE_Pressed, WeaponComponent, &USTUWeaponComponent::Zoom, true);
    PlayerInputComponent->BindAction<FZoomInputSignature>("Zoom", IE_Released, WeaponComponent, &USTUWeaponComponent::Zoom, false);
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

void ASTUPlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    CheckCameraOverlap();
}

void ASTUPlayerCharacter::OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    CheckCameraOverlap();
}

void ASTUPlayerCharacter::CheckCameraOverlap() const
{
    const auto HideMesh = CameraCollision->IsOverlappingComponent(GetCapsuleComponent());
    GetMesh()->SetOwnerNoSee(HideMesh);
    
    TArray<USceneComponent*> MeshChildren;
    GetMesh()->GetChildrenComponents(true, MeshChildren);
    for(const auto Component : MeshChildren)
    {
        const auto Primitive = Cast<UPrimitiveComponent>(Component);
        if(Primitive) Primitive->SetOwnerNoSee(HideMesh);
    }
}

void ASTUPlayerCharacter::OnDeath()
{
    Super::OnDeath();
    if(Controller)
    {
        GetController()->ChangeState(NAME_Spectating);
        if(WeaponComponent) WeaponComponent->Zoom(false);
    }
    UGameplayStatics::PlaySound2D(GetWorld(), AmbientDeathSound);
}
