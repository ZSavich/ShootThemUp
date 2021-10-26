
#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "STUSpectatorWidget.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUSpectatorWidget : public USTUBaseWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "Spectator")
    bool GetRespawnCountDown(int32& CountDown);
};
