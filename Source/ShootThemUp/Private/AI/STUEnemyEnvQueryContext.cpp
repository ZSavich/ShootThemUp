// Shoot Them Up. All rights reserved.


#include "AI/STUEnemyEnvQueryContext.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void USTUEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{

    const APawn* QueryOwner = Cast<APawn>(QueryInstance.Owner.Get());
    if(!QueryOwner) return;
    
    const auto Controller = Cast<AAIController>(QueryOwner->GetController());
    if(!Controller || !Controller->GetBlackboardComponent()) return;
    
    const auto EnemyActor = Cast<APawn>(Controller->GetBlackboardComponent()->GetValueAsObject(EnemyActorKeyName));   
    if(!EnemyActor) return;
    UE_LOG(LogTemp, Warning, TEXT("USTUEnemyEnvQueryContext::ProvideContext 4"));
    UEnvQueryItemType_Actor::SetContextHelper(ContextData, EnemyActor);
}
