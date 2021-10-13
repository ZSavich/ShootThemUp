// Shoot Them Up. All rights reserved.


#include "Notifies/STUEquipFinishedNotify.h"

void USTUEquipFinishedNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    OnNotify.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}
