
#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "STUGameInstance.h"
#include "STUMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class USTULevelItemWidget;
class USTUGameInstance;

UCLASS()
class SHOOTTHEMUP_API USTUMenuWidget : public USTUBaseWidget
{
	GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Widget")
    TSubclassOf<USTULevelItemWidget> LevelItemWidgetClass;
    
    UPROPERTY(meta = (BindWidget))
    UButton* StartLevelButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QuitGameButton;

    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* LevelItemsBox;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* HideAnimation;

    UFUNCTION()
    void OnStartLevel();

    UFUNCTION()
    void OnQuitGame();

    TArray<USTULevelItemWidget*> LevelItemWidgets;
    
    void OnLevelSelected(const FLevelData& LevelData);
    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

private:
    void InitLevelItems();
    USTUGameInstance* GetSTUGameInstance() const;
};
