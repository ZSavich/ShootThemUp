// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;
class USkeletalMeshComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUWeaponComponent();
    
    virtual void StartFire();
    virtual void NextWeapon();
    void StopFire();
    void Reload();
    bool GetWeaponUIData(FWeaponUIData& UIData) const;
    bool GetWeaponAmmoData(FAmmoData& AmmoData) const;
    bool TryToAddAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType, const int32 ClipsAmount);

protected:    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    TArray<FWeaponData> WeaponData;    

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    FName EquipWeaponSocketName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    FName SpareWeaponSocketName;
    
    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    UAnimMontage* EquipMontage;
    
    UPROPERTY(VisibleInstanceOnly, Category = "Weapons")
    ASTUBaseWeapon* CurrentWeapon;
    
    UPROPERTY(VisibleInstanceOnly, Category = "Weapons")
    TArray<ASTUBaseWeapon*> Weapons;

    int32 CurrentWeaponIndex;
    bool bCanFire;

    
	virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    
    void OnClipEmpty(ASTUBaseWeapon* TriggerWeapon);
    void EquipWeapon(const int32 WeaponIndex);
    
    FORCEINLINE bool CanFire() const {return !bReloadAnimInProgress && !bEquipAnimInProgress && CurrentWeapon;}
    FORCEINLINE bool CanEquip() const {return !bEquipAnimInProgress && !bReloadAnimInProgress;}

    
private:
    bool bEquipAnimInProgress;
    bool bReloadAnimInProgress;

    UPROPERTY()
    UAnimMontage* CurrentReloadMontage;
    
    void SpawnWeapon();
    void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* Component,
        const FName& SocketName) const;
    
    void PlayAnimMontage(UAnimMontage* Montage) const;
    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* Mesh);
    void OnReloadFinished(USkeletalMeshComponent* Mesh);
    
    FORCEINLINE bool CanReload() const {return !bReloadAnimInProgress && !bEquipAnimInProgress && CurrentWeapon;}
};

