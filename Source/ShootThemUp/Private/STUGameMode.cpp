// Shoot Them Up. All rights reserved.


#include "STUGameMode.h"

#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"

ASTUGameMode::ASTUGameMode()
{
    DefaultPawnClass = ASTUBaseCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
}
