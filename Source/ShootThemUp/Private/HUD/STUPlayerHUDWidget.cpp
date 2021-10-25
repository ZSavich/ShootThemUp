// Shoot Them Up. All rights reserved.


#include "HUD/STUPlayerHUDWidget.h"

#include "STUGameMode.h"
#include "STUHealthComponent.h"
#include "STUWeaponComponent.h"
#include "STUUtils.h"
#include "STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerHUD, All, Log);

void USTUPlayerHUDWidget::NativeOnInitialized()
{
    if(GetWorld())
    {
        GameMode = Cast<ASTUGameMode>(GetWorld()->GetAuthGameMode());
    }
    Super::NativeOnInitialized();
}

void USTUPlayerHUDWidget::BindWidgetsToPlayer()
{
    HealthComponent = STUUtils::GetPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
    WeaponComponent = STUUtils::GetPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
    if(HealthComponent)
    HealthComponent->OnHealthChanged.AddUObject(this,&USTUPlayerHUDWidget::OnHealthChange);
}

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

void USTUPlayerHUDWidget::OnHealthChange(const float Health, const float HealthDelta)
{
    if(HealthDelta<0.f) OnTakeDamage();
}

bool USTUPlayerHUDWidget::GetRoundData(FRoundData& RoundData)
{
    if(!GameMode)
    {
        if(!GetWorld()) return false;
        GameMode = Cast<ASTUGameMode>(GetWorld()->GetAuthGameMode());
    }
    RoundData = GameMode->GetRoundData();
    return true;
}

bool USTUPlayerHUDWidget::GetPlayerStatistic(FPlayerStatistic& PlayerStatistic) const
{
    const auto PlayerState = GetOwningPlayer()->GetPlayerState<ASTUPlayerState>();
    if(!PlayerState) return false;
    PlayerStatistic = PlayerState->GetPlayerStatistic();
    return true;
}

