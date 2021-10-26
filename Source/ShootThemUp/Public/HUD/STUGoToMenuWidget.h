#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "STUGoToMenuWidget.generated.h"

class UButton;

UCLASS()
class SHOOTTHEMUP_API USTUGoToMenuWidget : public USTUBaseWidget
{
	GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* GoToMenuButton;

    UFUNCTION()
    void OnGoToMenu();
};
