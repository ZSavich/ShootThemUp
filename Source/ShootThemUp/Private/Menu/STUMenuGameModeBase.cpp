

#include "Menu/STUMenuGameModeBase.h"

#include "Menu/STUMenuHUD.h"
#include "Menu/STUMenuPlayerController.h"

ASTUMenuGameModeBase::ASTUMenuGameModeBase()
{
    HUDClass = ASTUMenuHUD::StaticClass();
    PlayerControllerClass = ASTUMenuPlayerController::StaticClass();
}
