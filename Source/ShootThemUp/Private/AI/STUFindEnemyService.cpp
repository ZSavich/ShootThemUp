// Shoot Them Up. All rights reserved.


#include "AI/STUFindEnemyService.h"

#include "AIController.h"
#include "STUAIPerceptionComponent.h"
#include "STUUtils.h"
#include "BehaviorTree/BlackboardComponent.h"

USTUFindEnemyService::USTUFindEnemyService()
{
    NodeName="FindEnemyService";
}

void USTUFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if(!Controller || !Blackboard) return;
    
    const auto PerceptionComponent = STUUtils::GetPlayerComponent<USTUAIPerceptionComponent>(Controller);
    if(!PerceptionComponent) return;
    
    const auto EnemyPawn = PerceptionComponent->GetClosestPawn();
    if(!EnemyPawn)
        Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, nullptr);
    else
        Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, EnemyPawn);
}
