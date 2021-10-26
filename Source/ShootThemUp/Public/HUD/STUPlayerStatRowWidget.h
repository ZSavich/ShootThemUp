// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "STUPlayerStatRowWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class SHOOTTHEMUP_API USTUPlayerStatRowWidget : public USTUBaseWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* PlayerNameTextBlock;
    UPROPERTY(meta = (BindWidget))
    UTextBlock* KillsTextBlock;
    UPROPERTY(meta = (BindWidget))
    UTextBlock* DeathTextBlock;
    UPROPERTY(meta = (BindWidget))
    UTextBlock* TeamTextBlock;
    UPROPERTY(meta = (BindWidget))
    UImage* TeamColor;
    UPROPERTY(meta = (BindWidget))
    UImage* PlayerIndicatorImage;

public:
    void SetPlayerName(const FText& Name) const;
    void SetKills(const FText& Kills) const;
    void SetDeaths(const FText& Deaths) const;
    void SetTeam(const FText& Team) const;
    void SetTeamColor(const FLinearColor& Color) const;
    void SetPlayerIndicatorVisibility(const bool Visible) const;
};
