// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerHUDWidget.generated.h"

class USTUHealthComponent;
class USTUWeaponComponent;

UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual bool Initialize() override;
    void CleanComponents() {HealthComponent = nullptr; WeaponComponent = nullptr;}
    
protected:

    UPROPERTY()
    USTUHealthComponent* HealthComponent;

    UPROPERTY()
    USTUWeaponComponent* WeaponComponent;
    
    UFUNCTION(BlueprintPure)
    float GetHealthPercent();

    UFUNCTION(BlueprintPure)
    bool GetWeaponUIData(FWeaponUIData& UIData);

    UFUNCTION(BlueprintPure)
    bool GetWeaponAmmoData(FAmmoData& AmmoData);

    UFUNCTION(BlueprintPure)
    bool IsPlayerAlive() ;

    UFUNCTION(BlueprintPure)
    bool IsPlayerSpectating() const;

    UFUNCTION(BlueprintImplementableEvent, Category = "UMG")
    void OnTakeDamage();

private:
    void OnHealthChange(const float Health, const float HealthDelta);
};
