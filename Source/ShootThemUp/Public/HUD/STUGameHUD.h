// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUCoreTypes.h"
#include "STUGameHUD.generated.h"

class USTUPlayerHUDWidget;
class USTUPauseWidget;

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
    TSubclassOf<USTUPauseWidget> PauseWidget;

    UPROPERTY()
    TMap<EMatchState, UUserWidget*> GameWidgets;

    UPROPERTY()
    UUserWidget* CurrentWidget = nullptr;;
    
    virtual void BeginPlay() override;
    
    void OnMatchStateChanged(const EMatchState State);
    void DrawCrossHair();
};
