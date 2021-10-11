// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUBaseWeapon();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USkeletalMeshComponent* Mesh;
    
	virtual void BeginPlay() override;
};
