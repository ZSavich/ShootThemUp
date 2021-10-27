// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "STUSoundFuncLib.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUSoundFuncLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    static void SetSoundClassVolume(USoundClass* SoundClass, const float Volume);
    UFUNCTION(BlueprintCallable)
    static void ToggleSoundClassVolume(USoundClass* SoundClass);
};
