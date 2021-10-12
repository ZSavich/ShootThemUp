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
    
    virtual void StartFire();
    virtual void StopFire();
    virtual void MakeShot();
    virtual bool GetTraceData(FVector& StartPoint, FVector& EndPoint) const;

protected:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USkeletalMeshComponent* Mesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSettigns")
    FName MuzzleSocketName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSettings")
    float ShotMagnitude;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSettings")
    float DamageAmount;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSettings")
    TSubclassOf<UDamageType> DamageType;
    
	virtual void BeginPlay() override;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    
private:    
    APlayerController* GetPlayerController() const;
    
    void MakeHit(FHitResult& HitResult, const FVector& StartPoint, const FVector& EndPoint) const;
    void MakeDamage(AActor* const TargetActor);
    
    FORCEINLINE FVector GetMuzzleWorldLocation() const {return Mesh->GetSocketLocation(MuzzleSocketName);}
};
