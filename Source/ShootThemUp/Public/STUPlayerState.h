// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "GameFramework/PlayerState.h"
#include "STUPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
    FORCEINLINE FString GetCharacterName() const {return CharacterName;}
    FORCEINLINE void SetCharacterName(const FString& Name) {CharacterName = Name;}
    
    FORCEINLINE int32 GetTeamID() const {return TeamID;}
    FORCEINLINE void SetTeamID(const int32& ID) {TeamID=ID;}

    FORCEINLINE FLinearColor GetTeamColor() const {return TeamColor;}
    FORCEINLINE void SetTeamColor(const FLinearColor& Color) {TeamColor=Color;}

    FORCEINLINE void AddKill() {++PlayerStatistic.KillsNum;}
    FORCEINLINE int32 GetKillsNum() const {return PlayerStatistic.KillsNum;}

    FORCEINLINE void AddDeath() {++PlayerStatistic.DeathsNum;}
    FORCEINLINE int32 GetDeathsNum() const {return PlayerStatistic.DeathsNum;}

    FORCEINLINE FPlayerStatistic GetPlayerStatistic() const {return PlayerStatistic;}
    
private:
    int32 TeamID = 0;
    FLinearColor TeamColor = FLinearColor::Red;
    FString CharacterName = "Default";
    
    FPlayerStatistic PlayerStatistic;
};
