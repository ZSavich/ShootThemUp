// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/STUWeaponComponent.h"
#include "STUAIWeaponComponent.generated.h"


UCLASS()
class SHOOTTHEMUP_API USTUAIWeaponComponent : public USTUWeaponComponent
{
	GENERATED_BODY()

public:
    virtual void StartFire() override;
    virtual void NextWeapon() override;
    
    bool NeedPickupAmmo(const TSubclassOf<ASTUBaseWeapon> SearchWeapon, const int32& MinCount) const;
};
