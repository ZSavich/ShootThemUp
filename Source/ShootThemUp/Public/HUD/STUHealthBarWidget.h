// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "STUHealthBarWidget.generated.h"

class UProgressBar;

UCLASS()
class SHOOTTHEMUP_API USTUHealthBarWidget : public USTUBaseWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthProgressBar;

    UPROPERTY(EditDefaultsOnly, Category = "Visibility")
    float PercentVisibilityThreshold = 0.8;

    UPROPERTY(EditDefaultsOnly, Category = "Visibility")
    float PercentColorThreshold = 0.3;

    UPROPERTY(EditDefaultsOnly, Category = "Visibility")
    FLinearColor GoodColor = FLinearColor::Blue;

    UPROPERTY(EditDefaultsOnly, Category = "Visibility")
    FLinearColor BadColor = FLinearColor::Red;

public:
    void SetHealthPercent(const float& Percent);
};
