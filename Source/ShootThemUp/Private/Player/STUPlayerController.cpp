// Shoot Them Up. All rights reserved.


#include "Player/STUPlayerController.h"
#include "Components/STURespawnComponent.h"
#include "STUGameHUD.h"
#include "STUGameInstance.h"
#include "STUGameMode.h"
#include "STUPlayerHUDWidget.h"
#include "STUSoundFuncLib.h"
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
    InputComponent->BindAction("Mute", IE_Pressed, this, &ASTUPlayerController::OnSoundMute);
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
    if(State == EMatchState::EMS_InProgress)
    {
        bShowMouseCursor = false;
        SetInputMode(FInputModeGameOnly());
    } else
    {
        bShowMouseCursor = true;
        SetInputMode(FInputModeUIOnly());
    }
}

void ASTUPlayerController::OnSoundMute()
{
    if(!GetWorld() || !GetWorld()->GetGameInstance()) return;
    const auto MasterClass = GetWorld()->GetGameInstance<USTUGameInstance>()->GetMasterSoundClass();
    USTUSoundFuncLib::ToggleSoundClassVolume(MasterClass);
}
