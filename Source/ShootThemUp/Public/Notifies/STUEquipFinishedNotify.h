// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "STUEquipFinishedNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifySignature, USkeletalMeshComponent*);

UCLASS()
class SHOOTTHEMUP_API USTUEquipFinishedNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
    FOnNotifySignature OnNotify;
    
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
