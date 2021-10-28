#include "Components/STURespawnComponent.h"
#include "STUGameMode.h"

USTURespawnComponent::USTURespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTURespawnComponent::Respawn(const int32& RespawnTimer)
{
    if(!GetWorld()) return;

    RespawnCountDown = RespawnTimer;
    GetWorld()->GetTimerManager().SetTimer(RespawnTimeHandle,this,&USTURespawnComponent::RespawnTimerUpdate,
        1.f,true);
}

void USTURespawnComponent::RespawnTimerUpdate()
{
    if(--RespawnCountDown <= 0)
    {
        if(!GetWorld()) return;
        GetWorld()->GetTimerManager().ClearTimer(RespawnTimeHandle);
        
        const auto GameMode = Cast<ASTUGameMode>(GetWorld()->GetAuthGameMode());
        if(!GameMode) return;
        GameMode->RespawnRequest(Cast<AController>(GetOwner()));
    }
}

bool USTURespawnComponent::IsRespawnInProcess() const
{
    return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimeHandle);
}

