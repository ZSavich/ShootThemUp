// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;
class APlayerController;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUBaseWeapon();
    
    virtual void StartFire(){};
    virtual void StopFire(){};
    virtual void MakeShot(){};
    virtual bool GetTraceData(FVector& StartPoint, FVector& EndPoint) const;
    void ChangeClip();
    bool TryToAddAmmo(const int32& ClipsAmount);
    
    FAmmoData GetWeaponAmmo() const {return CurrentAmmo;}
    FORCEINLINE FWeaponUIData GetUIData() const {return UIData;};
    FORCEINLINE bool CanReload() const {return CurrentAmmo.Bullets != DefaultAmmo.Bullets && (CurrentAmmo.Clips != 0 || CurrentAmmo.Infinite);};
    FORCEINLINE bool IsClipEmpty() const {return CurrentAmmo.Bullets <= 0;}
    FORCEINLINE bool IsAmmoEmpty() const {return IsClipEmpty() && CurrentAmmo.Clips <= 0 && !CurrentAmmo.Infinite;}
    
    FOnClipEmpty OnClipEmpty;
    
protected:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USkeletalMeshComponent* Mesh;

    UPROPERTY(EditDefaultsOnly, Category = "AmmoData")
    FAmmoData DefaultAmmo;

    UPROPERTY(EditDefaultsOnly, Category = "HUD")
    FWeaponUIData UIData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSettigns")
    FName MuzzleSocketName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSettings")
    float ShotMagnitude;
    
	virtual void BeginPlay() override;
    
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    
    APlayerController* GetPlayerController() const;
    
    void MakeHit(FHitResult& HitResult, const FVector& StartPoint, const FVector& EndPoint) const;

    void DecreaseBullet();
   
    FORCEINLINE bool IsAmmoFull() const {return CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Bullets == DefaultAmmo.Bullets;}
    FORCEINLINE FVector GetMuzzleWorldLocation() const {return Mesh->GetSocketLocation(MuzzleSocketName);}

private:
    FAmmoData CurrentAmmo;
};
