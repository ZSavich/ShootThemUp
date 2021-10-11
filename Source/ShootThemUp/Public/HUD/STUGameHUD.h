// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUGameHUD.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUGameHUD : public AHUD
{
	GENERATED_BODY()

private:
    virtual void DrawHUD() override;
    void DrawCrossHair();
};
