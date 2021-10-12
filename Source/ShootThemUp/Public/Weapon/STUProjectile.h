// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUProjectile();

    FORCEINLINE void SetShotDirection(const FVector& Direction) {ShotDirection = Direction;}
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USphereComponent* SphereComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UProjectileMovementComponent* MovementComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ProjectileSettings")
    float DamageAmount;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ProjectileSettings")
    float DamageRadius;
    
	virtual void BeginPlay() override;
    
    AController* GetController() const;
    
private:
    FVector ShotDirection;

    UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );
};
