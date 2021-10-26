// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUCoreTypes.h"
#include "STUGameHUD.generated.h"

class USTUBaseWidget;
class USTUPlayerHUDWidget;
class USTUPauseWidget;
class USTUGameOverWidget;

UCLASS()
class SHOOTTHEMUP_API ASTUGameHUD : public AHUD
{
	GENERATED_BODY()

public:

    virtual void DrawHUD() override;
    
    UPROPERTY()
    USTUPlayerHUDWidget* PlayerWidget;
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
    TSubclassOf<USTUPlayerHUDWidget> PlayerHUDWidget;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
    TSubclassOf<USTUPauseWidget> PauseWidgetClass;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
    TSubclassOf<USTUGameOverWidget> GameOverWidgetClass;
    
    UPROPERTY()
    TMap<EMatchState, USTUBaseWidget*> GameWidgets;

    UPROPERTY()
    USTUBaseWidget* CurrentWidget = nullptr;;
    
    virtual void BeginPlay() override;
    
    void OnMatchStateChanged(const EMatchState State);
    void DrawCrossHair();
};
