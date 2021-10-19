// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STUFindEnemyService.generated.h"

struct FBlackboardKeySelector;

UCLASS()
class SHOOTTHEMUP_API USTUFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
    USTUFindEnemyService();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;
    
protected:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
