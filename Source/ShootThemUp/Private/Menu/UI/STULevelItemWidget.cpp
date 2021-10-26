#include "Menu/UI/STULevelItemWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USTULevelItemWidget::NativeOnInitialized()
{
    if(LevelSelectButton)
        LevelSelectButton->OnClicked.AddDynamic(this, &USTULevelItemWidget::OnLevelItemClicked);
    if(FrameImage)
        FrameImage->SetVisibility(ESlateVisibility::Hidden);
    Super::NativeOnInitialized();
}

void USTULevelItemWidget::OnLevelItemClicked()
{
    OnLevelSelected.Broadcast(LevelData);
}

void USTULevelItemWidget::SetSelected(const bool Selected) const
{
    return Selected ? FrameImage->SetVisibility(ESlateVisibility::Visible) :
                        FrameImage->SetVisibility(ESlateVisibility::Hidden);
}

void USTULevelItemWidget::SetLevelData(const FLevelData& NewLevelData)
{
    LevelData = NewLevelData;
    if(LevelImage)
        LevelImage->SetBrushFromTexture(LevelData.LevelThumb);
    if(LevelNameTextBlock)
        LevelNameTextBlock->SetText(FText::FromName(LevelData.LevelName));
}
