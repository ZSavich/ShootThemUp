// Shoot Them Up. All rights reserved.


#include "AI/STUAmmoCheckerDecorator.h"

#include "AIController.h"
#include "STUAIWeaponComponent.h"
#include "STUBaseWeapon.h"
#include "STUUtils.h"

USTUAmmoCheckerDecorator::USTUAmmoCheckerDecorator()
{
    NodeName = "Ammo Checker";
    Weapon = nullptr;
    MinClips = 1;
}

bool USTUAmmoCheckerDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if(!Controller) return false;
    
    const auto WeaponComponent = STUUtils::GetPlayerComponent<USTUAIWeaponComponent>(Controller->GetPawn());
    if(!WeaponComponent) return false;
    return WeaponComponent->NeedPickupAmmo(Weapon, MinClips);
}


