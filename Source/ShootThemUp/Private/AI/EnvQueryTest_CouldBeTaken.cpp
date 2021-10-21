// Shoot Them Up. All rights reserved.


#include "AI/EnvQueryTest_CouldBeTaken.h"

#include "STUBasePickup.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"

UEnvQueryTest_CouldBeTaken::UEnvQueryTest_CouldBeTaken()
{
    Cost = EEnvTestCost::Low;
    ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
    SetWorkOnFloatValues(false);
}

void UEnvQueryTest_CouldBeTaken::RunTest(FEnvQueryInstance& QueryInstance) const
{
    const auto DataOwner = QueryInstance.Owner.Get();
    BoolValue.BindData(DataOwner, QueryInstance.QueryID);

    const bool bWantsToBeTaken = BoolValue.GetValue();
    for(FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        const auto PickupItem = Cast<ASTUBasePickup>(GetItemActor(QueryInstance, It.GetIndex()));
        if(!PickupItem) return;
        It.SetScore(TestPurpose, FilterType, PickupItem->CanBeTaken(), bWantsToBeTaken);
    }
}

