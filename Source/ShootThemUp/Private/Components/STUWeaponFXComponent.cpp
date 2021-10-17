// Shoot Them Up. All rights reserved.


#include "Components/STUWeaponFXComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponFXComponent::BeginPlay()
{
    Super::BeginPlay();
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& HitResult)
{
    auto ImpactData = DefaultImpactData;
    if(HitResult.PhysMaterial.IsValid())
    {
        const auto PhysMaterial = HitResult.PhysMaterial.Get();
        if(ImpactDataMap.Contains(PhysMaterial))
        {
            ImpactData = ImpactDataMap[PhysMaterial];
        }
    }
    
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactData.NiagaraEffect, HitResult.ImpactPoint,
        HitResult.ImpactNormal.Rotation());

    const auto ImpactDecal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), ImpactData.DecalData.Decal, ImpactData.DecalData.Size,
        HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation(),ImpactData.DecalData.LifeTime);
    ImpactDecal->SetFadeOut(ImpactData.DecalData.LifeTime,ImpactData.DecalData.FadeOutTime);
}

