// Shoot Them Up. All rights reserved.


#include "Components/STUWeaponFXComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponFXComponent::BeginPlay()
{
    Super::BeginPlay();
    checkf(DefaultImpactFX, TEXT("USTUWeaponFXComponent DefaultImpactFX is Not Valid!"));
}

void USTUWeaponFXComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& HitResult)
{
    auto Effect = DefaultImpactFX;
    if(HitResult.PhysMaterial.IsValid())
    {
        const auto PhysMaterial = HitResult.PhysMaterial.Get();
        if(ImpactFXMap.Contains(PhysMaterial))
        {
            Effect = ImpactFXMap[PhysMaterial];
        }
    }
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
}

