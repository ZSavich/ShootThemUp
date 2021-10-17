// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUWeaponFXComponent();

    void PlayImpactFX(const FHitResult& HitResult);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ImpactFX")
    UNiagaraSystem* DefaultImpactFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ImpactFX")
    TMap<UPhysicalMaterial*, UNiagaraSystem*> ImpactFXMap;
    
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
