// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "STUNextLocationTask.generated.h"

struct FBlackboardKeySelector;

UCLASS()
class SHOOTTHEMUP_API USTUNextLocationTask : public UBTTaskNode
{
	GENERATED_BODY()

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    
public:
    USTUNextLocationTask();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Location")
    float Radius;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Location")
    FBlackboardKeySelector AimLocationKey;
};
