// Shoot Them Up. All rights reserved.


#include "STUGameMode.h"
#include "HUD/STUGameHUD.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "AI/STUAICharacter.h"
#include "AI/STUAIController.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameRound, All, Log);

ASTUGameMode::ASTUGameMode()
{
    DefaultPawnClass = ASTUBaseCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
    HUDClass = ASTUGameHUD::StaticClass();
}

void ASTUGameMode::StartPlay()
{
    Super::StartPlay();
    SpawnPawns();

    CurrentRound = 1;
    StartRound();
}

void ASTUGameMode::SpawnPawns()
{
    if(!AIControllerClass) return;

    for(auto i = 0; i < GameData.PlayersNum; i++)
    {
        FActorSpawnParameters SpawnParameters;
        SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        
        const auto PawnAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass,SpawnParameters);
        RestartPlayer(PawnAIController);
    }
}

UClass* ASTUGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if(InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASTUGameMode::StartRound()
{
    if(CurrentRound <= GameData.RoundsNum)
    {
        RoundCountDown = GameData.RoundTime;
        GetWorldTimerManager().SetTimer(GameTimerHandle,this,&ASTUGameMode::GameTimerUpdate,1.f,true);
        return;
    }
    UE_LOG(LogGameRound, Display, TEXT("================= GAME OVER ================="));
}

void ASTUGameMode::GameTimerUpdate()
{
    UE_LOG(LogGameRound, Display, TEXT("Time: %i ||| Round: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNum);
    if(--RoundCountDown <= 0)
    {
        GetWorldTimerManager().ClearTimer(GameTimerHandle);
        CurrentRound++;
        StartRound();
    }
}
