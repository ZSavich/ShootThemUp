#include "HUD/STUPauseWidget.h"

#include "STUGameMode.h"
#include "Components/Button.h"

void USTUPauseWidget::NativeOnInitialized()
{
    if(ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &USTUPauseWidget::OnClearPause);
    }
    Super::NativeOnInitialized();
}
void USTUPauseWidget::OnClearPause()
{
    if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
    const auto GameMode = Cast<ASTUGameMode>(GetWorld()->GetAuthGameMode());
    if(!GameMode) return;
    GameMode->ClearPause();
}
