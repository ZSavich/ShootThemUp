// Shoot Them Up. All rights reserved.


#include "AI/STUAICharacter.h"
#include "BrainComponent.h"
#include "STUAIWeaponComponent.h"
#include "STUHealthBarWidget.h"
#include "STUHealthComponent.h"
#include "AI/STUAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer.SetDefaultSubobjectClass<USTUAIWeaponComponent>("WeaponComponent"))
{
    PrimaryActorTick.bCanEverTick = true;
    
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = ASTUAIController::StaticClass();

    GetCharacterMovement()->bUseControllerDesiredRotation = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f,300.f,0.f);
    bUseControllerRotationYaw = false;

    HealthBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
    HealthBarComponent->SetupAttachment(GetRootComponent());
    HealthBarComponent->SetDrawAtDesiredSize(true);
    HealthBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
    HealthBarComponent->SetRelativeLocation(FVector(0.f,0.f,120.f));

    HealthVisibilityDistance = 1000.f;
}

void ASTUAICharacter::OnDeath()
{
    Super::OnDeath();

    const auto AIController = Cast<AAIController>(GetController());
    if(!AIController) return;
    AIController->BrainComponent->Cleanup();
}

void ASTUAICharacter::UpdateHealthBar()
{
    checkf(HealthBarComponent, TEXT("ASTUAICharacter::UpdateHealthBar ERROR()"));

    const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
    const auto Distance = FVector::Distance(GetActorLocation(),PlayerLocation);
    
    if(Distance > HealthVisibilityDistance)
    {
        HealthBarComponent->SetVisibility(false);
        return;
    }

    HealthBarComponent->SetVisibility(true);
    const auto HealthBar = Cast<USTUHealthBarWidget>(HealthBarComponent->GetUserWidgetObject());
    if(!HealthBar) return;
    
    HealthBar->SetHealthPercent(HealthComponent->GetHealthPercent());
}

void ASTUAICharacter::Tick(float DeltaSeconds)
{
    UpdateHealthBar();
    Super::Tick(DeltaSeconds);
}

void ASTUAICharacter::OnHealthChanged(const float Health, const float HealthDelta)
{
    Super::OnHealthChanged(Health, HealthDelta);
}
