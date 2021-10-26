// Shoot Them Up. All rights reserved.


#include "HUD/STUPlayerStatRowWidget.h"
#include "STUPlayerStatRowWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USTUPlayerStatRowWidget::SetPlayerName(const FText& Name) const
{
    if(!PlayerNameTextBlock) return;
    PlayerNameTextBlock->SetText(Name);
}

void USTUPlayerStatRowWidget::SetKills(const FText& Kills) const
{
    if(!KillsTextBlock) return;
    KillsTextBlock->SetText(Kills);
}

void USTUPlayerStatRowWidget::SetDeaths(const FText& Deaths) const
{
    if(!DeathTextBlock) return;
    DeathTextBlock->SetText(Deaths);
}

void USTUPlayerStatRowWidget::SetTeam(const FText& Team) const
{
    if(!TeamTextBlock) return;
    TeamTextBlock->SetText(Team);
}

void USTUPlayerStatRowWidget::SetTeamColor(const FLinearColor& Color) const
{
    if(!TeamColor) return;
    TeamColor->SetColorAndOpacity(Color);
}

void USTUPlayerStatRowWidget::SetPlayerIndicatorVisibility(const bool Visible) const
{
    if(!PlayerIndicatorImage) return;
    PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
