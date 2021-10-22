#pragma once
#include "STUPlayerState.h"
#include "GameFramework/Controller.h"

class STUUtils
{
public:
    template <typename T>
    static T* GetPlayerComponent(const AActor* PlayerPawn)
    {
        if(!PlayerPawn) return nullptr;

        const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
        const auto ResultComponent = Cast<T>(Component);
        if(!ResultComponent) return nullptr;
        return ResultComponent;
    }

    bool static AreEnemy(AController* Controller1, AController* Controller2)
    {
        if(!Controller1 || !Controller2 || Controller1 == Controller2) return false;
        const auto PlayerPawn1 = Cast<APawn>(Controller1->GetPawn());
        const auto PlayerPawn2 = Cast<APawn>(Controller2->GetPawn());
        
        if(!PlayerPawn1 || !PlayerPawn2) return false;
        const auto PlayerStat1 = Cast<ASTUPlayerState>(PlayerPawn1->GetPlayerState());
        const auto PlayerState2 = Cast<ASTUPlayerState>(PlayerPawn2->GetPlayerState());
        
        return PlayerStat1 && PlayerState2 && PlayerStat1->GetTeamID() != PlayerState2->GetTeamID();
    }
};