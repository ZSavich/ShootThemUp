// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "STUCoreTypes.h"
#include "STUAnimNotify.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
    FOnNotifySignature OnNotify;
    
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
