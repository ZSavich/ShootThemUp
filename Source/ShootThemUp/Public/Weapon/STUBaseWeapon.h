// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;
class APlayerController;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUBaseWeapon();
    
    virtual void Fire();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USkeletalMeshComponent* Mesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSettigns")
    FName MuzzleSocketName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSettings")
    float ShotMagnitude;
    
    
	virtual void BeginPlay() override;

    void MakeShot();
    APlayerController* GetPlayerController() const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    bool GetTraceData(FVector& StartPoint, FVector& EndPoint) const;
    void MakeHit(FHitResult& HitResult, const FVector& StartPoint, const FVector& EndPoint) const;
    
    FORCEINLINE FVector GetMuzzleWorldLocation() const {return Mesh->GetSocketLocation(MuzzleSocketName);}
};
