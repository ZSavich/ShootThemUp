// Shoot Them Up. All rights reserved.


#include "Dev/STUDevDamageActor.h"

#include "Components/BillboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ASTUDevDamageActor::ASTUDevDamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    SetRootComponent(Scene);
    
    BillboardComp = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillboardComponent"));
    BillboardComp->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ASTUDevDamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASTUDevDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    UKismetSystemLibrary::DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);

    UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, DamageType,
        {}, this, nullptr, bDoFullDamage);
}

