
#include "Menu/UI/STUMenuWidget.h"

#include "STUGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USTUMenuWidget::NativeOnInitialized()
{
    StartLevelButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartLevel);
    Super::NativeOnInitialized();
}

void USTUMenuWidget::OnStartLevel()
{
    if(!GetWorld()) return;
    const auto GameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
    if(!GameInstance || GameInstance->GetStartupLevelName().IsNone())
    {
        UE_LOG(LogTemp, Error, TEXT("GameInstance LevelName = None;"));
        return;
    }
    UGameplayStatics::OpenLevel(GetWorld(),GameInstance->GetStartupLevelName());
}
