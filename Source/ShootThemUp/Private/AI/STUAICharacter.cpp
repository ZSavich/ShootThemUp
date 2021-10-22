// Shoot Them Up. All rights reserved.


#include "AI/STUAICharacter.h"

#include "BrainComponent.h"
#include "STUAIWeaponComponent.h"
#include "AI/STUAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer.SetDefaultSubobjectClass<USTUAIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = ASTUAIController::StaticClass();

    GetCharacterMovement()->bUseControllerDesiredRotation = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f,300.f,0.f);
    bUseControllerRotationYaw = false;
}

void ASTUAICharacter::OnDeath()
{
    Super::OnDeath();

    const auto AIController = Cast<AAIController>(GetController());
    if(!AIController) return;
    AIController->BrainComponent->Cleanup();
}
