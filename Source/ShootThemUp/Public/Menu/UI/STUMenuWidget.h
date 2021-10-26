
#pragma once

#include "CoreMinimal.h"
#include "STUGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "STUMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class USTULevelItemWidget;
class USTUGameInstance;

UCLASS()
class SHOOTTHEMUP_API USTUMenuWidget : public UUserWidget
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

    UFUNCTION()
    void OnStartLevel();

    UFUNCTION()
    void OnQuitGame();

    TArray<USTULevelItemWidget*> LevelItemWidgets;
    
    void OnLevelSelected(const FLevelData& LevelData);

private:
    void InitLevelItems();
    USTUGameInstance* GetSTUGameInstance() const;
};
