// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STUCoreTypes.h"
#include "STUGameMode.generated.h"

class AAIController;
class ASTUAICharacter;

UCLASS()
class SHOOTTHEMUP_API ASTUGameMode : public AGameModeBase
{
	GENERATED_BODY()
    
public:
    ASTUGameMode();
    
    virtual void StartPlay() override;
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

    void Killed(AController* KillerController, AController* VictimController) const;
    void RespawnRequest(AController* Controller);

    FORCEINLINE FRoundData GetRoundData() const {return RoundData;}
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Players")
    FGameData GameData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Players")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Players")
    TSubclassOf<ASTUAICharacter> AIPawnClass;
    
    FTimerHandle GameTimerHandle;
    FRoundData RoundData;
    
    void SpawnPawns();
    void StartRound();
    void GameTimerUpdate();

    void ResetPlayers();
    void ResetOnePlayer(AController* Controller);

    void CreateTeamsInfo();
    FLinearColor DetermineColorByTeamID(const int32& TeamID);
    void SetPlayerColor(AController* Controller) const;

    void StartRespawn(const APawn* Pawn) const;

    void GameOver() const;
};
