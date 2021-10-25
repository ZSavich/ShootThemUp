// Shoot Them Up. All rights reserved.


#include "HUD/STUGameHUD.h"

#include "STUGameMode.h"
#include "Engine/Canvas.h"
#include "STUPlayerHUDWidget.h"
#include "STUPauseWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameHUD, All, Log)

void ASTUGameHUD::BeginPlay()
{
    Super::BeginPlay();

    PlayerWidget = CreateWidget<USTUPlayerHUDWidget>(GetWorld(), PlayerHUDWidget);
    GameWidgets.Add(EMatchState::EMS_InProgress, PlayerWidget);
    GameWidgets.Add(EMatchState::EMS_Pause, CreateWidget<USTUPauseWidget>(GetWorld(), PauseWidget));

    for(const auto GameWidgetTuple : GameWidgets)
    {
        const auto GameWidget = GameWidgetTuple.Value;
        if(!GameWidget) continue;
        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if(!GetWorld()) return;
    const auto GameMode = Cast<ASTUGameMode>(GetWorld()->GetAuthGameMode());
    if(GameMode)
    {
        GameMode->OnMatchStateChanged.AddUObject(this, &ASTUGameHUD::OnMatchStateChanged);
    }
}

void ASTUGameHUD::OnMatchStateChanged(const EMatchState State)
{
    if(CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }
    if(GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
    }
    if(CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }
}

void ASTUGameHUD::DrawHUD()
{
    Super::DrawHUD();
    //DrawCrossHair(); // Debug CrossHair
}

void ASTUGameHUD::DrawCrossHair()
{
    const TInterval<float> Center (Canvas->SizeX * 0.5, Canvas->SizeY * 0.5);

    constexpr float LineMagnitude = 10.f;
    constexpr float LineThickness = 3.f;
    const FLinearColor LineColor = FLinearColor::Green;

    DrawLine(Center.Min - LineMagnitude, Center.Max, Center.Min + LineMagnitude,
        Center.Max, LineColor, LineThickness);
    DrawLine(Center.Min, Center.Max - LineMagnitude, Center.Min,
        Center.Max + LineMagnitude, LineColor, LineThickness);
}
