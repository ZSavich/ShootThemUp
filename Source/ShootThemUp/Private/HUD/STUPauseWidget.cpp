#include "HUD/STUPauseWidget.h"

#include "STUGameMode.h"
#include "Components/Button.h"

bool USTUPauseWidget::Initialize()
{
    const auto Result = Super::Initialize();
    if(ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &USTUPauseWidget::OnClearPause);
    }
    return Result;
}

void USTUPauseWidget::OnClearPause()
{
    if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
    const auto GameMode = Cast<ASTUGameMode>(GetWorld()->GetAuthGameMode());
    if(!GameMode) return;
    GameMode->ClearPause();
}
