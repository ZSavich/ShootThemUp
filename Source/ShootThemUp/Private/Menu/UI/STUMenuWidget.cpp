
#include "Menu/UI/STUMenuWidget.h"
#include "STUGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STULevelItemWidget.h"
#include "Components/HorizontalBox.h"

DEFINE_LOG_CATEGORY_STATIC(LogMenuWidget, All, Log)

void USTUMenuWidget::NativeOnInitialized()
{
    if(StartLevelButton)
    {
        StartLevelButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartLevel);
    }
    if(QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnQuitGame);
    }
    InitLevelItems();
    Super::NativeOnInitialized();
}

void USTUMenuWidget::InitLevelItems()
{
    LevelItemsBox->ClearChildren();
    
    const auto STUGameInstance = GetSTUGameInstance();
    if(!STUGameInstance || !STUGameInstance->GetLevelsData().Num())
    {
        UE_LOG(LogMenuWidget, Error, TEXT("GameInstance Level List in Empty!"));
        return;
    }

    for(const auto LevelItem: STUGameInstance->GetLevelsData())
    {
        const auto LevelItemWidget = CreateWidget<USTULevelItemWidget>(this, LevelItemWidgetClass);
        LevelItemWidget->SetLevelData(LevelItem);
        LevelItemWidget->OnLevelSelected.AddUObject(this, &USTUMenuWidget::OnLevelSelected);
        LevelItemWidgets.Add(LevelItemWidget);
        LevelItemsBox->AddChild(LevelItemWidget);
    }
    
    if(STUGameInstance->GetStartupLevel().LevelName.IsNone())
        OnLevelSelected(STUGameInstance->GetLevelsData()[0]);
    else
        OnLevelSelected(STUGameInstance->GetStartupLevel());
}

void USTUMenuWidget::OnLevelSelected(const FLevelData& LevelData)
{   
    const auto STUGameInstance = GetSTUGameInstance();
    GetSTUGameInstance()->SetStartupLevel(LevelData);
    
    for(const auto LevelItemWidget: LevelItemWidgets)
    {
        const bool bIsStartup = LevelItemWidget->GetLevelData().LevelName == LevelData.LevelName;
        LevelItemWidget->SetSelected(bIsStartup);
        
        if(!bIsStartup) continue;
        STUGameInstance->SetStartupLevel(LevelItemWidget->GetLevelData());
    }
}

void USTUMenuWidget::OnStartLevel()
{
    if(!GetWorld()) return;
    const auto GameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
    if(!GameInstance || GameInstance->GetStartupLevel().LevelName.IsNone())
    {
        UE_LOG(LogTemp, Error, TEXT("GameInstance LevelName = None;"));
        return;
    }
    UGameplayStatics::OpenLevel(GetWorld(),GameInstance->GetStartupLevel().LevelName);
}

void USTUMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

USTUGameInstance* USTUMenuWidget::GetSTUGameInstance() const
{
    if(!GetWorld()) return nullptr;
    return GetWorld()->GetGameInstance<USTUGameInstance>();
}
