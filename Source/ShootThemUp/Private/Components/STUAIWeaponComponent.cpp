// Shoot Them Up. All rights reserved.


#include "Components/STUAIWeaponComponent.h"

#include "STUBaseWeapon.h"

void USTUAIWeaponComponent::StartFire()
{
    if(!CanFire() || !bCanFire) return;
    if(CurrentWeapon->IsAmmoEmpty())
        NextWeapon();
    else
        CurrentWeapon->StartFire();
}

void USTUAIWeaponComponent::NextWeapon()
{
    if(!CanEquip()) return;
    auto NextWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    while(NextWeaponIndex != CurrentWeaponIndex)
    {
        if(!Weapons[NextWeaponIndex]->IsAmmoEmpty()) break;
        NextWeaponIndex = (NextWeaponIndex + 1) % Weapons.Num();
    }
    if(NextWeaponIndex != CurrentWeaponIndex)
    {
        CurrentWeaponIndex = NextWeaponIndex;
        EquipWeapon(CurrentWeaponIndex);
        bCanFire = true;
        return;
    }
    bCanFire = false;
}
