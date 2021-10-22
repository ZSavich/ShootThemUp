
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUSpectatorWidget.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUSpectatorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "Spectator")
    bool GetRespawnCountDown(int32& CountDown);
};
