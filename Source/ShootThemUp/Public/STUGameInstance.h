// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGameInstance : public UGameInstance
{
	GENERATED_BODY()
    
private:
    UPROPERTY(EditDefaultsOnly, Category = "Levels")
    FName StartupLevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, Category = "Levels")
    FName MenuLevelName = NAME_None;

public:
    FName GetStartupLevelName() const {return StartupLevelName;}
    FName GetMenuLevelName() const {return MenuLevelName;}
};
