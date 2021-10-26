// Shoot Them Up. All rights reserved.


#include "HUD/STUHealthBarWidget.h"
#include "Components/ProgressBar.h"

void USTUHealthBarWidget::SetHealthPercent(const float& Percent)
{
    if(!HealthProgressBar) return;

    const auto HealthVisibility = (Percent < PercentVisibilityThreshold && Percent > 0.f) ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
    HealthProgressBar->SetVisibility(HealthVisibility);

    const auto Color = Percent > PercentColorThreshold ? GoodColor : BadColor;
    HealthProgressBar->SetFillColorAndOpacity(Color);
    
    HealthProgressBar->SetPercent(Percent);
}
