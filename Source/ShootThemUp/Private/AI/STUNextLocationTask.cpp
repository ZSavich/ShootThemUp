// Shoot Them Up. All rights reserved.


#include "AI/STUNextLocationTask.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"

USTUNextLocationTask::USTUNextLocationTask()
{
    NodeName = "NextLocation";
}

EBTNodeResult::Type USTUNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto AIController = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if(!AIController || !Blackboard) return EBTNodeResult::Failed;

    const auto Pawn = AIController->GetPawn();
    if(!Pawn) return EBTNodeResult::Failed;
    
    const auto NavSystem = UNavigationSystemV1::GetCurrent(Pawn);
    if(!NavSystem) return EBTNodeResult::Failed;

    FNavLocation Result;
    const bool bSuccess = NavSystem->GetRandomReachablePointInRadius(Pawn->GetActorLocation(),Radius,Result);
    if(!bSuccess) return EBTNodeResult::Failed;

    Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, Result.Location);
    return EBTNodeResult::Succeeded;
}