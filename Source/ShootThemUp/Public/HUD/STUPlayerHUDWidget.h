// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "STUCoreTypes.h"
#include "STUPlayerHUDWidget.generated.h"

class USTUHealthComponent;
class USTUWeaponComponent;
class ASTUGameMode;
class UProgressBar;


UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public USTUBaseWidget
{
	GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;
    void BindWidgetsToPlayer();
    
protected:

    UPROPERTY()
    USTUHealthComponent* HealthComponent;

    UPROPERTY()
    USTUWeaponComponent* WeaponComponent;

    UPROPERTY()
    ASTUGameMode* GameMode;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* DamageAnimation;

    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthProgressBar;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HealthBar")
    float HealthBarThreshold = 0.5f;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HealthBar")
    FLinearColor GoodColor = FLinearColor::Blue;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HealthBar")
    FLinearColor BadColor = FLinearColor::Red;

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

    void UpdateHealthBar();

private:
    void OnHealthChange(const float Health, const float HealthDelta);
};
