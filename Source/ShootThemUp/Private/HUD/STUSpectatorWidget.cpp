#include "HUD/STUSpectatorWidget.h"

#include "STURespawnComponent.h"
#include "STUUtils.h"

bool USTUSpectatorWidget::GetRespawnCountDown(int32& CountDown)
{
    const auto SpawnComponent = GetOwningPlayer() ?
        STUUtils::GetPlayerComponent<USTURespawnComponent>(GetOwningPlayer()) : nullptr;
    
    if(!SpawnComponent || !SpawnComponent->IsRespawnInProcess()) return false;
    CountDown = SpawnComponent->GetRespawnCountDown();
    return true;
}
