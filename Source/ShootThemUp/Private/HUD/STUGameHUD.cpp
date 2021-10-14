// Shoot Them Up. All rights reserved.


#include "HUD/STUGameHUD.h"

#include "Engine/Canvas.h"
#include "STUPlayerHUDWidget.h"

ASTUGameHUD::ASTUGameHUD()
{
   
}

void ASTUGameHUD::BeginPlay()
{
    Super::BeginPlay();
    PlayerWidget = CreateWidget<USTUPlayerHUDWidget>(GetWorld(),PlayerHUDWidget);
    PlayerWidget->AddToViewport();
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
