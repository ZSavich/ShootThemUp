// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUDevDamageActor.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUDevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUDevDamageActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* Scene;

    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    //UBillboardComponent* BillboardComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere")
    float Radius;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere")
    FLinearColor SphereColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    float Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    bool bDoFullDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    TSubclassOf<UDamageType> DamageType;  

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
