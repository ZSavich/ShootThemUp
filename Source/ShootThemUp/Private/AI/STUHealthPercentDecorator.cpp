// Shoot Them Up. All rights reserved.


#include "AI/STUHealthPercentDecorator.h"

#include "AIController.h"
#include "STUHealthComponent.h"
#include "STUUtils.h"

USTUHealthPercentDecorator::USTUHealthPercentDecorator()
{
    NodeName="Health Percent";
    HealthPercent = 0.6;
}

bool USTUHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if(!Controller) return false;

    const auto HealthComponent = STUUtils::GetPlayerComponent<USTUHealthComponent>(Controller->GetPawn());
    if(!HealthComponent || HealthComponent->IsDeath()) return false;

    return HealthComponent->GetHealthPercent() <= HealthPercent;
}
