// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUWeaponComponent();
    
    void StartFire();
    void StopFire();
    void NextWeapon();
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    TArray<TSubclassOf<ASTUBaseWeapon>> WeaponClasses;    

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    FName EquipWeaponSocketName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    FName SpareWeaponSocketName;
    
	virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:    
    UPROPERTY(VisibleInstanceOnly, Category = "Weapons")
    ASTUBaseWeapon* CurrentWeapon;
    
    UPROPERTY(VisibleInstanceOnly, Category = "Weapons")
    TArray<ASTUBaseWeapon*> Weapons;

    int32 CurrentWeaponIndex;
    
    void SpawnWeapon();
    void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* Component,
        const FName& SocketName) const;
    void EquipWeapon(const int32 WeaponIndex);
};
