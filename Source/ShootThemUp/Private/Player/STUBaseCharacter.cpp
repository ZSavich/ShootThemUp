// Shoot Them Up. All rights reserved.


#include "Player/STUBaseCharacter.h"

#include "Components/STUHealthComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/STUWeaponComponent.h"

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(GetRootComponent());
    CameraBoom->bUsePawnControlRotation = true;
    CameraBoom->TargetArmLength = 300.f;
    CameraBoom->SocketOffset = FVector(0.f, 70.f, 200.f);
    
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraFollow"));
    FollowCamera->SetupAttachment(CameraBoom);

    HealthComponent = CreateDefaultSubobject<USTUHealthComponent>(TEXT("HealthComponent"));
    WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>(TEXT("WeaponComponent"));

    HealthRenderText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HealthTextRender"));
    HealthRenderText->SetupAttachment(GetRootComponent());
    HealthRenderText->SetOwnerNoSee(true);
    HealthRenderText->SetRelativeRotation(FRotator(0.f,180.f,0.f));
    HealthRenderText->SetRelativeLocation(FVector(0.f,0.f,100.f));
    HealthRenderText->HorizontalAlignment = EHorizTextAligment::EHTA_Center;

    WalkSpeed = 600.f;
    SprintSpeed = 900.f;

    LandedDamageVelocity = FVector2D(900.f, 1600.f);
    LandedDamage = FVector2D(10.f, 100.f);

    LifeSpan = 5.f;
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
    SetMovementStatus(EMovementStatus::EMS_Normal);

    check(HealthComponent);
    check(HealthRenderText);
    check(GetMovementComponent());

    OnHealthChanged(HealthComponent->GetHealth(), 0.f);
    HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);
    LandedDelegate.AddDynamic(this, &ASTUBaseCharacter::OnGroundLanded);
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
    check(PlayerInputComponent)
    check(WeaponComponent)
    
    PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);   
    PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &APawn::AddControllerYawInput);
    
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASTUBaseCharacter::Sprint);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASTUBaseCharacter::StopSprinting);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTUWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUWeaponComponent::StopFire);
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USTUWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTUWeaponComponent::Reload);
}

float ASTUBaseCharacter::GetMovementDirection() const
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

void ASTUBaseCharacter::OnDeath()
{
    //if(DeathMontage) PlayAnimMontage(DeathMontage);
    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
    
    if(Controller) GetController()->ChangeState(NAME_Spectating);

    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
    SetLifeSpan(LifeSpan);
    WeaponComponent->StopFire();
}

void ASTUBaseCharacter::OnHealthChanged(const float Health, const float HealthDelta) const
{
    HealthRenderText->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void ASTUBaseCharacter::OnGroundLanded(const FHitResult& HitResult)
{
    const auto LandedVelocityZ = -GetVelocity().Z;
    
    if(LandedVelocityZ < LandedDamageVelocity.X) return;

    const auto FinalLandedDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity,
        LandedDamage, LandedVelocityZ);
    TakeDamage(FinalLandedDamage, FDamageEvent{},nullptr, nullptr);
}



