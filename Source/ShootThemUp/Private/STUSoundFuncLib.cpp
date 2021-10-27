// Shoot Them Up. All rights reserved.


#include "STUSoundFuncLib.h"

#include "STUGameInstance.h"
#include "Sound/SoundClass.h"

void USTUSoundFuncLib::SetSoundClassVolume(USoundClass* SoundClass, const float Volume)
{
    if(!SoundClass || !GEngine->GameViewport->GetWorld() || !GEngine->GameViewport->GetWorld()->GetGameInstance()) return;
    
    const auto GameInstance = GEngine->GameViewport->GetWorld()->GetGameInstance<USTUGameInstance>();
    SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.f, 1.f);
    GameInstance->SetSoundVolume(Volume);
}

void USTUSoundFuncLib::ToggleSoundClassVolume(USoundClass* SoundClass)
{
    if(!SoundClass || !GEngine->GameViewport->GetWorld() || !GEngine->GameViewport->GetWorld()->GetGameInstance()) return;
    const auto GameInstance = GEngine->GameViewport->GetWorld()->GetGameInstance<USTUGameInstance>();
    SoundClass->Properties.Volume = SoundClass->Properties.Volume == 0.f ? GameInstance->GetSoundVolume() : 0.f;
}