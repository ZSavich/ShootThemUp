// Shoot Them Up. All rights reserved.


#include "AI/STUFireService.h"

#include "AIController.h"
#include "STUUtils.h"
#include "STUWeaponComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

USTUFireService::USTUFireService()
{
    NodeName="FireService";
}

void USTUFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    const auto Enemy = Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);
    if(!Controller || !Blackboard || !Enemy) return;

    const auto WeaponComponent = STUUtils::GetPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
    WeaponComponent ? WeaponComponent->StartFire() : WeaponComponent->StopFire();

    
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
