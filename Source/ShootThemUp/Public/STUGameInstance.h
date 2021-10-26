
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUCoreTypes.h"
#include "STUGameInstance.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUGameInstance : public UGameInstance
{
	GENERATED_BODY()
    
public:
    TArray<FLevelData>& GetLevelsData() {return LevelsData;}

    FORCEINLINE FLevelData GetStartupLevel() const {return StartupLevel; }
    FORCEINLINE void SetStartupLevel(const FLevelData& LevelData) {StartupLevel=LevelData;}

    FORCEINLINE FName GetMenuLevelName() const {return MenuLevelName;}
    
private:
    UPROPERTY(EditDefaultsOnly, Category = "Levels", meta = (ToolTip = "LevelName must me unique!"))
    TArray<FLevelData> LevelsData;

    FLevelData StartupLevel;
    FName MenuLevelName = "Menu";
};
