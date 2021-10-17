// Shoot Them Up. All rights reserved.


#include "Components/STUWeaponFXComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& HitResult)
{
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
    
}


// Called when the game starts
void USTUWeaponFXComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void USTUWeaponFXComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

