// Shoot Them Up. All rights reserved.


#include "Player/STUPlayerController.h"
#include "Components/STURespawnComponent.h"
#include "STUGameHUD.h"
#include "STUPlayerHUDWidget.h"
#include "GameFramework/HUD.h"

ASTUPlayerController::ASTUPlayerController()
{
    RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>(TEXT("RepsawnComponent"));
}

void ASTUPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    const auto HUD = Cast<ASTUGameHUD>(GetHUD());
    if(HUD && HUD->PlayerWidget) HUD->PlayerWidget->BindWidgetsToPlayer();
}
