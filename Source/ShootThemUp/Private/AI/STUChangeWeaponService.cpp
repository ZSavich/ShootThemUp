// Shoot Them Up. All rights reserved.


#include "AI/STUChangeWeaponService.h"

#include "AIController.h"
#include "STUUtils.h"
#include "STUWeaponComponent.h"

USTUChangeWeaponService::USTUChangeWeaponService()
{
    NodeName = "ChangeWeapon";
    Probability = 0.5;
}

void USTUChangeWeaponService::ChangeWeapon(UBehaviorTreeComponent& OwnerComp) const
{
    const auto RandFloat = FMath::RandRange(0.f,1.f);
    if(RandFloat > Probability) return;

    const auto Controller = OwnerComp.GetAIOwner();
    if(!Controller) return;
    
    const auto WeaponComponent = STUUtils::GetPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
    if(!WeaponComponent) return;
    
    WeaponComponent->NextWeapon();
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    ChangeWeapon(OwnerComp);
}
