// Shoot Them Up. All rights reserved.


#include "AI/STUAICharacter.h"

#include "AI/STUAIController.h"

ASTUAICharacter::ASTUAICharacter()
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ASTUAIController::StaticClass();
}
