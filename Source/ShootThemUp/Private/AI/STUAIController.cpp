// Shoot Them Up. All rights reserved.


#include "AI/STUAIController.h"
#include "STURespawnComponent.h"
#include "STUAICharacter.h"
#include "STUAIPerceptionComponent.h"

ASTUAIController::ASTUAIController()
{
    PrimaryActorTick.bCanEverTick = true;
    PerceptionComp = CreateDefaultSubobject<USTUAIPerceptionComponent>(TEXT("PerceptionComponent"));
    SetPerceptionComponent(*PerceptionComp);

    RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>(TEXT("RepsawnComponent"));

    bWantsPlayerState = true;
}

void ASTUAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    const auto AICharacter = Cast<ASTUAICharacter>(GetPawn());
    if(!AICharacter) return;
    
    RunBehaviorTree(BehaviorTreeAsset);
}

void ASTUAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    SetFocus(GetFocusOnActor());
}

APawn* ASTUAIController::GetFocusOnActor() const
{
    const auto FocusPawn = PerceptionComp->GetClosestPawn();
    if(!FocusPawn) return nullptr;
    return FocusPawn;
}
