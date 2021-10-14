// Shoot Them Up. All rights reserved.


#include "HUD/STUPlayerHUDWidget.h"

#include "STUHealthComponent.h"
#include "STUWeaponComponent.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerHUD, All, Log);

float USTUPlayerHUDWidget::GetHealthPercent()
{
    if(!HealthComponent)
    {
        HealthComponent = STUUtils::GetPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
        return 0;
    }
    return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData)
{
    if(!WeaponComponent)
    {
        WeaponComponent = STUUtils::GetPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
        return false;
    }
    WeaponComponent->GetWeaponUIData(UIData);
    return true;
}

bool USTUPlayerHUDWidget::GetWeaponAmmoData(FAmmoData& AmmoData)
{
    if(!WeaponComponent)
    {
        WeaponComponent = STUUtils::GetPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
        return false;
    }
    WeaponComponent->GetWeaponAmmoData(AmmoData);
    return true;
}

bool USTUPlayerHUDWidget::IsPlayerAlive() 
{
    if(!HealthComponent)
    {
        HealthComponent = STUUtils::GetPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
        return false;
    }
    return HealthComponent && !HealthComponent->IsDeath(); 
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == (NAME_Spectating);
}


