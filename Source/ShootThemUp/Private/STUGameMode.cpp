// Shoot Them Up. All rights reserved.


#include "STUGameMode.h"

#include "EngineUtils.h"
#include "STUPlayerState.h"
#include "STURespawnComponent.h"
#include "STUUtils.h"
#include "STUWeaponComponent.h"
#include "HUD/STUGameHUD.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "AI/STUAICharacter.h"
#include "AI/STUAIController.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameRound, All, Log);

static const int32 MinRoundTimeForRespawn = 10;

ASTUGameMode::ASTUGameMode()
{
    DefaultPawnClass = ASTUBaseCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
    HUDClass = ASTUGameHUD::StaticClass();
}

void ASTUGameMode::StartPlay()
{
    Super::StartPlay();

    RoundData.RoundsNum = GameData.RoundsNum;
    
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
    if(RoundData.CurrentRound <= GameData.RoundsNum)
    {
        ResetPlayers();
        RoundData.RoundCountDown = GameData.RoundTime;
        GetWorldTimerManager().SetTimer(GameTimerHandle,this,&ASTUGameMode::GameTimerUpdate,1.f,true);
    }
    else
    {
        GameOver();
    }
    
}

void ASTUGameMode::GameTimerUpdate()
{
    if(--RoundData.RoundCountDown <= 0)
    {
        GetWorldTimerManager().ClearTimer(GameTimerHandle);
        RoundData.CurrentRound++;
        StartRound();
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

        PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
        PlayerState->SetTeamID(TeamID);
        SetPlayerColor(Controller);
        TeamID = TeamID == 1 ? 2 : 1;
    }
}

FLinearColor ASTUGameMode::DetermineColorByTeamID(const int32& TeamID)
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

void ASTUGameMode::Killed(AController* KillerController, AController* VictimController) const
{
    const auto KillerPawn = KillerController ? Cast<ASTUBaseCharacter>(KillerController->GetPawn()) : nullptr;
    const auto VictimPawn = VictimController ? Cast<ASTUBaseCharacter>(VictimController->GetPawn()) : nullptr;

    if(KillerPawn)
    {
        const auto KillerState = Cast<ASTUPlayerState>(KillerPawn->GetPlayerState());
        KillerState->AddKill();
    }

    if(VictimPawn)
    {
        const auto VictimState = Cast<ASTUPlayerState>(VictimPawn->GetPlayerState());
        VictimState->AddDeath();
    }
    StartRespawn(VictimPawn);
}

void ASTUGameMode::RespawnRequest(AController* Controller)
{
    ResetOnePlayer(Controller);
}

void ASTUGameMode::StartRespawn(const APawn* Pawn) const
{
    if(RoundData.RoundCountDown > GameData.RespawnTime + MinRoundTimeForRespawn)
    {
        const auto RespawnComponent = STUUtils::GetPlayerComponent<USTURespawnComponent>(Pawn->GetController());
        
        if(!RespawnComponent) return;
        RespawnComponent->Respawn(GameData.RespawnTime);
    }
}

void ASTUGameMode::GameOver() const
{
    for(const auto Pawn: TActorRange<APawn>(GetWorld()))
    {
        if(Pawn)
        {
            const auto WeaponComponent = STUUtils::GetPlayerComponent<USTUWeaponComponent>(Pawn);
            if(WeaponComponent) WeaponComponent->StopFire();
            
            Pawn->TurnOff();
            Pawn->DisableInput(nullptr);
        }
    }
}
