#include "Menu/UI/STULevelItemWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USTULevelItemWidget::NativeOnInitialized()
{
    if(LevelSelectButton)
        LevelSelectButton->OnClicked.AddDynamic(this, &USTULevelItemWidget::OnLevelItemClicked);
        LevelSelectButton->OnHovered.AddDynamic(this, &USTULevelItemWidget::OnLevelItemHovered);
        LevelSelectButton->OnUnhovered.AddDynamic(this, &USTULevelItemWidget::OnLevelItemUnHovered);
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
    LevelImage->SetColorAndOpacity(Selected ? FLinearColor::Red : FLinearColor::White);
}

void USTULevelItemWidget::OnLevelItemHovered()
{
    FrameImage->SetVisibility(ESlateVisibility::Visible);
           
}

void USTULevelItemWidget::OnLevelItemUnHovered()
{
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
