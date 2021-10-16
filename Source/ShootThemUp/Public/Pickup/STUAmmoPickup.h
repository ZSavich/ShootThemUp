// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickup/STUBasePickup.h"
#include "STUAmmoPickup.generated.h"

class ASTUBaseWeapon;

UCLASS()
class SHOOTTHEMUP_API ASTUAmmoPickup : public ASTUBasePickup
{
	GENERATED_BODY()
    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    int32 ClipsAmount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    TSubclassOf<ASTUBaseWeapon> WeaponType;
    
    virtual bool GivePickupTo(const APawn* Pawn) override;
};
