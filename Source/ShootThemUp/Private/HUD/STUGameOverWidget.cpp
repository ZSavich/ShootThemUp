// Shoot Them Up. All rights reserved.


#include "HUD/STUGameOverWidget.h"
#include "Components/VerticalBox.h"
#include "STUGameMode.h"
#include "STUPlayerState.h"
#include "STUPlayerStatRowWidget.h"
#include "STUUtils.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USTUGameOverWidget::NativeOnInitialized()
{
    if(GetWorld())
    {
        const auto GameMode = Cast<ASTUGameMode>(GetWorld()->GetAuthGameMode());
        if(GameMode)
            GameMode->OnMatchStateChanged.AddUObject(this, &USTUGameOverWidget::OnMatchStateChange);
    }
    if(ResetLevelButton)
    {
        ResetLevelButton->OnClicked.AddDynamic(this, &USTUGameOverWidget::OnResetLevel);
    }
    //Show();
    Super::NativeOnInitialized();
}

void USTUGameOverWidget::OnMatchStateChange(const EMatchState State)
{
    if(State == EMatchState::EMS_GameOver)
    {
        UpdatePlayerStat();
    }
}

void USTUGameOverWidget::OnResetLevel()
{
    const auto LevelName = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(GetWorld(), FName(LevelName));
}

void USTUGameOverWidget::UpdatePlayerStat()
{
    if(!GetWorld()) return;

    PlayerStatBox->ClearChildren();
    
    for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if(!Controller) return;
        
        const auto PlayerState = Controller->GetPlayerState<ASTUPlayerState>();
        if(!PlayerState) return;
        
        const auto PlayerStatRow = CreateWidget<USTUPlayerStatRowWidget>(this,PlayerStatRowClass);
        if(!PlayerStatRow) return;

        PlayerStatRow->SetPlayerName(FText::FromString(PlayerState->GetCharacterName()));
        PlayerStatRow->SetKills(STUUtils::TextFromInt(PlayerState->GetKillsNum()));
        PlayerStatRow->SetDeaths(STUUtils::TextFromInt(PlayerState->GetDeathsNum()));
        PlayerStatRow->SetTeam(STUUtils::TextFromInt(PlayerState->GetTeamID()));
        PlayerStatRow->SetTeamColor(PlayerState->GetTeamColor());
        PlayerStatRow->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
        PlayerStatBox->AddChildToVerticalBox(PlayerStatRow);
    }
}
