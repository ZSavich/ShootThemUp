// Shoot Them Up. All rights reserved.


#include "HUD/STUBaseWidget.h"

void USTUBaseWidget::Show()
{
    if(!ShowAnimation || IsPlayingAnimation()) return;
    PlayAnimation(ShowAnimation);
}
