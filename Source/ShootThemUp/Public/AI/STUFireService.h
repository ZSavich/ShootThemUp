// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STUFireService.generated.h"

struct FBlackboardKeySelector;

UCLASS()
class SHOOTTHEMUP_API USTUFireService : public UBTService
{
	GENERATED_BODY()

public:
    USTUFireService();
    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
    
};
