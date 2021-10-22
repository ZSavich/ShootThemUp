// Shoot Them Up. All rights reserved.


#include "STUGameMode.h"

#include "STUPlayerState.h"
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
    CurrentRound = 1;
    SpawnPawns();
    CreateTeamsInfo();
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
        ResetPlayers();
    }
}

void ASTUGameMode::ResetPlayers() 
{
    if(!GetWorld()) return;
    
    for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePlayer(It->Get());
    }
}

void ASTUGameMode::ResetOnePlayer(AController* Controller)
{
    if(Controller && Controller->GetPawn()) {
        Controller->GetPawn()->Reset();
    }
    RestartPlayer(Controller);
    SetPlayerColor(Controller);
}

void ASTUGameMode::CreateTeamsInfo()
{
    if(!GetWorld()) return;
    int32 TeamID = 1;

    for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = Cast<AController>(It->Get());
        if(!Controller) continue;

        const auto Pawn = Cast<ASTUBaseCharacter>(Controller->GetPawn());
        if(!Pawn) continue;

        const auto PlayerState = Cast<ASTUPlayerState>(Pawn->GetPlayerState());
        if(!PlayerState) continue;

        PlayerState->SetTeamColor(DetermineColorBeTeamID(TeamID));
        PlayerState->SetTeamID(TeamID);
        SetPlayerColor(Controller);
        TeamID = TeamID == 1 ? 2 : 1;
    }
}

FLinearColor ASTUGameMode::DetermineColorBeTeamID(const int32& TeamID)
{
    if(TeamID - 1 < GameData.TeamColors.Num())
        return GameData.TeamColors[TeamID - 1];
    return GameData.DefaultTeamColor;
}

void ASTUGameMode::SetPlayerColor(AController* Controller) const
{
    if(!Controller) return;
    const auto Pawn = Cast<ASTUBaseCharacter>(Controller->GetPawn());
    if(!Pawn) return;
    
    const auto PlayerState = Cast<ASTUPlayerState>(Pawn->GetPlayerState());
    if(!PlayerState) return;
    
    Pawn->SetPlayerColor(PlayerState->GetTeamColor());
}
