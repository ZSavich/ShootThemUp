// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "STUGameOverWidget.generated.h"

class UVerticalBox;
class USTUPlayerStatRowWidget;

UCLASS()
class SHOOTTHEMUP_API USTUGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
    
public:
    virtual bool Initialize() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget")
    TSubclassOf<USTUPlayerStatRowWidget> PlayerStatRowClass;

    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayerStatBox;

    void OnMatchStateChange(const EMatchState State);
    void UpdatePlayerStat();
};
