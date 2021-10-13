// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;
class USkeletalMeshComponent;

USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    TSubclassOf<ASTUBaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    UAnimMontage* ReloadMontage;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUWeaponComponent();
    
    void StartFire();
    void StopFire();
    void NextWeapon();
    void Reload();
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    TArray<FWeaponData> WeaponData;    

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    FName EquipWeaponSocketName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    FName SpareWeaponSocketName;
    
    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    UAnimMontage* EquipMontage;
    
	virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    int32 CurrentWeaponIndex;
    bool bEquipAnimInProgress;
    bool bReloadAnimInProgress;
    
    UPROPERTY(VisibleInstanceOnly, Category = "Weapons")
    ASTUBaseWeapon* CurrentWeapon;
    
    UPROPERTY(VisibleInstanceOnly, Category = "Weapons")
    TArray<ASTUBaseWeapon*> Weapons;

    UPROPERTY()
    UAnimMontage* CurrentReloadMontage;
    
    void SpawnWeapon();
    void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* Component,
        const FName& SocketName) const;
    void EquipWeapon(const int32 WeaponIndex);
    
    void PlayAnimMontage(UAnimMontage* Montage) const;
    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* Mesh);
    void OnReloadFinished(USkeletalMeshComponent* Mesh);

    template<typename T>
    T* FindNotifyByMontage(const UAnimMontage* Montage);

    FORCEINLINE bool CanFire() const {return !bReloadAnimInProgress && !bEquipAnimInProgress && CurrentWeapon;}
    FORCEINLINE bool CanEquip() const {return !bEquipAnimInProgress;}
    FORCEINLINE bool CanReload() const {return !bReloadAnimInProgress && !bEquipAnimInProgress && CurrentWeapon;}
};

