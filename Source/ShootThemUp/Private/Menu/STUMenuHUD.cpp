
#include "Menu/STUMenuHUD.h"
#include "UI/STUMenuWidget.h"

void ASTUMenuHUD::BeginPlay()
{
    Super::BeginPlay();
    if(MenuWidgetClass)
    {
        const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(),MenuWidgetClass);
        if(MenuWidget)
        {
            MenuWidget->AddToViewport();
            MenuWidget->SetVisibility(ESlateVisibility::Visible);
        }
    }
}
