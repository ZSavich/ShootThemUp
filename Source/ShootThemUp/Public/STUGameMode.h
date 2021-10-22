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

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Players")
    FGameData GameData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Players")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Players")
    TSubclassOf<ASTUAICharacter> AIPawnClass;

    int32 CurrentRound;
    int32 RoundCountDown;
    FTimerHandle GameTimerHandle;
    
    void SpawnPawns();
    void StartRound();
    void GameTimerUpdate();

    void ResetPlayers();
    void ResetOnePlayer(AController* Controller);

    void CreateTeamsInfo();
    FLinearColor DetermineColorBeTeamID(const int32& TeamID);
    void SetPlayerColor(AController* Controller) const;
};
