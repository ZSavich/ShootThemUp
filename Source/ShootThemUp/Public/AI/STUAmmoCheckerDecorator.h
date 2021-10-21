// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STUAmmoCheckerDecorator.generated.h"

class ASTUBaseWeapon;

UCLASS()
class SHOOTTHEMUP_API USTUAmmoCheckerDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
    USTUAmmoCheckerDecorator();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
    TSubclassOf<ASTUBaseWeapon> Weapon;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
    int32 MinClips;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
