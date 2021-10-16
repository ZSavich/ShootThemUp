// Shoot Them Up. All rights reserved.


#include "Pickup/STUHealthPickup.h"

#include "STUHealthComponent.h"
#include "STUUtils.h"

bool ASTUHealthPickup::GivePickupTo(const APawn* Pawn)
{
    if(!Pawn) return false;
    const auto HealthComponent = STUUtils::GetPlayerComponent<USTUHealthComponent>(Pawn);
    
    if(!HealthComponent) return false;

    return HealthComponent->TryToAddHealth(HealthAmount);
}
