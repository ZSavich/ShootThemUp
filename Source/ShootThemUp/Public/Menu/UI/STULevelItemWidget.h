#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STULevelItemWidget.generated.h"

class UButton;
class UImage;
class UTextBlock;

UCLASS()
class SHOOTTHEMUP_API USTULevelItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    FOnLevelSelectedSignature OnLevelSelected;

    virtual void NativeOnInitialized() override;
    void SetSelected(const bool Selected) const;
    
    FORCEINLINE FLevelData GetLevelData() const {return LevelData;}
    void SetLevelData(const FLevelData& NewLevelData);

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* LevelSelectButton;

    UPROPERTY(meta = (BindWidget))
    UImage* LevelImage;

    UPROPERTY(meta = (BindWidget))
    UImage* FrameImage;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* LevelNameTextBlock;

private:
    FLevelData LevelData;

    UFUNCTION()
    void OnLevelItemClicked();
};
