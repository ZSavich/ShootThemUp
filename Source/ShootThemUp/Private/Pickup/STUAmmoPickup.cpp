// Shoot Them Up. All rights reserved.


#include "Pickup/STUAmmoPickup.h"

#include "STUHealthComponent.h"
#include "STUUtils.h"
#include "STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"

bool ASTUAmmoPickup::GivePickupTo(const APawn* Pawn)
{
    checkf(WeaponType, TEXT("ASTUAmmoPickup::GivePickupTo() WeaponType In Not Valid"))
    const auto HealthComponent = STUUtils::GetPlayerComponent<USTUHealthComponent>(Pawn);
    if(!HealthComponent || HealthComponent->IsDeath()) return false;

    const auto WeaponComponent = STUUtils::GetPlayerComponent<USTUWeaponComponent>(Pawn);
    if(!WeaponComponent || !WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount)) return false;
        
    return true;
}