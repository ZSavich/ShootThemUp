// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;
class APlayerController;

USTRUCT()
struct FAmmoData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, Category = "Ammo")
    int32 Bullets;

    UPROPERTY(EditDefaultsOnly, Category = "Ammo")
    int32 Clips;

    UPROPERTY(EditDefaultsOnly, Category = "Ammo")
    bool Infinite;
};

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
    
protected:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USkeletalMeshComponent* Mesh;

    UPROPERTY(EditDefaultsOnly, Category = "AmmoData")
    FAmmoData DefaultAmmo;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSettigns")
    FName MuzzleSocketName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSettings")
    float ShotMagnitude;
    
	virtual void BeginPlay() override;
    
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    
    APlayerController* GetPlayerController() const;
    
    void MakeHit(FHitResult& HitResult, const FVector& StartPoint, const FVector& EndPoint) const;

    void DecreaseBullet();
    void LogAmmo();
    
    FORCEINLINE bool IsAmmoEmpty() const {return IsClipEmpty() && CurrentAmmo.Clips <= 0 && !CurrentAmmo.Infinite;}
    FORCEINLINE bool IsClipEmpty() const {return CurrentAmmo.Bullets <= 0;}
    FORCEINLINE FVector GetMuzzleWorldLocation() const {return Mesh->GetSocketLocation(MuzzleSocketName);}

private:
    FAmmoData CurrentAmmo;

    
};
