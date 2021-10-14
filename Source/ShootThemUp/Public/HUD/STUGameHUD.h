// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUGameHUD.generated.h"

class USTUPlayerHUDWidget;

UCLASS()
class SHOOTTHEMUP_API ASTUGameHUD : public AHUD
{
	GENERATED_BODY()

public:
    ASTUGameHUD();

protected:
    virtual void BeginPlay() override;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
    TSubclassOf<USTUPlayerHUDWidget> PlayerHUDWidget;

private:
    virtual void DrawHUD() override;
    void DrawCrossHair();

    USTUPlayerHUDWidget* PlayerWidget;
};
