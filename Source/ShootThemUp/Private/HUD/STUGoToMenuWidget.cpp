
#include "HUD/STUGoToMenuWidget.h"

#include "STUGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USTUGoToMenuWidget::NativeOnInitialized()
{
    if(GoToMenuButton)
    {
        GoToMenuButton->OnClicked.AddDynamic(this, &USTUGoToMenuWidget::OnGoToMenu);
    }
    Super::NativeOnInitialized();
}

void USTUGoToMenuWidget::OnGoToMenu()
{
    if(!GetWorld()) return;
    const auto GameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
    if(!GameInstance || GameInstance->GetMenuLevelName().IsNone())
    {
        UE_LOG(LogTemp, Error, TEXT("GameInstance MenuLevelName is None!;"));
        return;
    }
    UGameplayStatics::OpenLevel(GetWorld(),GameInstance->GetMenuLevelName());
}
