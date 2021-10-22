// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerHUDWidget.generated.h"

class USTUHealthComponent;
class USTUWeaponComponent;
class ASTUGameMode;


UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual bool Initialize() override;
    void BindWidgetsToPlayer();
    
protected:

    UPROPERTY()
    USTUHealthComponent* HealthComponent;

    UPROPERTY()
    USTUWeaponComponent* WeaponComponent;

    UPROPERTY()
    ASTUGameMode* GameMode;
    
    UFUNCTION(BlueprintPure)
    float GetHealthPercent();

    UFUNCTION(BlueprintPure)
    bool GetWeaponUIData(FWeaponUIData& UIData);

    UFUNCTION(BlueprintPure)
    bool GetWeaponAmmoData(FAmmoData& AmmoData);

    UFUNCTION(BlueprintPure)
    bool GetRoundData(FRoundData& RoundData);

    UFUNCTION(BlueprintPure)
    bool GetPlayerStatistic(FPlayerStatistic& PlayerStatistic) const;

    UFUNCTION(BlueprintPure)
    bool IsPlayerAlive() ;

    UFUNCTION(BlueprintPure)
    bool IsPlayerSpectating() const;

    UFUNCTION(BlueprintImplementableEvent, Category = "UMG")
    void OnTakeDamage();

private:
    void OnHealthChange(const float Health, const float HealthDelta);
};
