// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUProjectile();
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    USphereComponent* SphereComponent;
    
protected:
	virtual void BeginPlay() override;
    

};
