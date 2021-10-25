// Shoot Them Up. All rights reserved.


#include "Player/STUPlayerController.h"
#include "Components/STURespawnComponent.h"
#include "STUGameHUD.h"
#include "STUGameMode.h"
#include "STUPlayerHUDWidget.h"
#include "GameFramework/HUD.h"

ASTUPlayerController::ASTUPlayerController()
{
    RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>(TEXT("RepsawnComponent"));
}

void ASTUPlayerController::BeginPlay()
{
    Super::BeginPlay();
    if(!GetWorld()) return;
    const auto GameMode = Cast<ASTUGameMode>(GetWorld()->GetAuthGameMode());
    if(!GameMode) return;
    GameMode->OnMatchStateChanged.AddUObject(this,&ASTUPlayerController::OnMatchStateChanged);
}

void ASTUPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    const auto HUD = Cast<ASTUGameHUD>(GetHUD());
    if(HUD && HUD->PlayerWidget) HUD->PlayerWidget->BindWidgetsToPlayer();
}

void ASTUPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    InputComponent->BindAction("Pause", IE_Pressed, this, &ASTUPlayerController::OnPauseGame);
}

void ASTUPlayerController::OnPauseGame()
{
    if(!GetWorld()) return;
    const auto GameMode = Cast<ASTUGameMode>(GetWorld()->GetAuthGameMode());
    if(!GameMode) return;
    GameMode->SetPause(this,nullptr);
    
}

void ASTUPlayerController::OnMatchStateChanged(const EMatchState State)
{
    if(State == EMatchState::EMS_Pause)
    {
        bShowMouseCursor = true;
        SetInputMode(FInputModeUIOnly());
    } else
    {
        bShowMouseCursor = false;
        SetInputMode(FInputModeGameOnly());
    }
}
