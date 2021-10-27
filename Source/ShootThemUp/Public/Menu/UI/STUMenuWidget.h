
#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "STUGameInstance.h"
#include "STUMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class USTULevelItemWidget;
class USTUGameInstance;
class USoundCue;

UCLASS()
class SHOOTTHEMUP_API USTUMenuWidget : public USTUBaseWidget
{
	GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget")
    TSubclassOf<USTULevelItemWidget> LevelItemWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sounds")
    USoundCue* GameStartSound;
    
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
