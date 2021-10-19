// Shoot Them Up. All rights reserved.


#include "AI/STUAIPerceptionComponent.h"

#include "Perception/AISense_Sight.h"

APawn* USTUAIPerceptionComponent::GetClosestPawn() const
{
    TArray<AActor*> PerceivedActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);
    if(!PerceivedActors.Num()) return nullptr;

    float ClosestDistance = MAX_FLT;
    APawn* ClosestPawn = nullptr;

    for (const auto Actor : PerceivedActors)
    {
        const auto Pawn = Cast<APawn>(Actor);
        if(!Pawn) return nullptr;

        const auto Distance = (GetOwner()->GetActorLocation() - Pawn->GetActorLocation()).Size();
        if(Distance < ClosestDistance)
        {
            ClosestDistance = Distance;
            ClosestPawn = Pawn;
        }
    }
    return ClosestPawn;
}
