// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USphereComponent;
class USoundCue;

UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUBasePickup();
    
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    virtual void Tick(float DeltaSeconds) override;
    
    FORCEINLINE bool CanBeTaken() const {return !GetWorldTimerManager().IsTimerActive(RespawnTimer);};

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USphereComponent* SphereCollision;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float RotationYaw;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sounds")
    USoundCue* PickupSound;
    
    FTimerHandle RespawnTimer;
    
	virtual void BeginPlay() override;

    void PickupWasTaken();
    void Respawn() const;
    void GenerateRotationYaw();
    virtual bool GivePickupTo(const APawn* Pawn);

};
