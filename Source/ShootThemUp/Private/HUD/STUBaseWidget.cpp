// Shoot Them Up. All rights reserved.


#include "HUD/STUBaseWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void USTUBaseWidget::Show()
{
    if(!ShowAnimation || IsPlayingAnimation()) return;
    PlayAnimation(ShowAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), OpenSound);
}

void USTUBaseWidget::STUOnVisibilityChanged(const ESlateVisibility InVisibility)
{
    if(InVisibility==ESlateVisibility::Visible)
    {
        Show();
    }
}

void USTUBaseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    OnVisibilityChanged.AddDynamic(this, &USTUBaseWidget::STUOnVisibilityChanged);
}
