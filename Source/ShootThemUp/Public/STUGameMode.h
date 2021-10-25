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

    FOnMatchStateChangedSignature OnMatchStateChanged;
    
    virtual void StartPlay() override;
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate) override;
    virtual bool ClearPause() override;

    void Killed(AController* KillerController, AController* VictimController) const;
    void RespawnRequest(AController* Controller);
    void SetMatchState(const EMatchState State);

    FORCEINLINE FRoundData GetRoundData() const {return RoundData;}
    FORCEINLINE EMatchState GetMatchState() const {return MatchState;}
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Players")
    FGameData GameData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Players")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Players")
    TSubclassOf<ASTUAICharacter> AIPawnClass;
    
    FTimerHandle GameTimerHandle;
    FRoundData RoundData;
    
    EMatchState MatchState;
    
    void SpawnPawns();
    void StartRound();
    void GameTimerUpdate();

    void ResetPlayers();
    void ResetOnePlayer(AController* Controller);

    void CreateTeamsInfo();
    FLinearColor DetermineColorByTeamID(const int32& TeamID);
    void SetPlayerColor(AController* Controller) const;

    
    void StartRespawn(const APawn* Pawn) const;
    void GameOver();
};
