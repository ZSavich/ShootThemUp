// Shoot Them Up. All rights reserved.


#include "Weapon/STUProjectile.h"
#include "Components/SphereComponent.h"

ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    SphereComponent->InitSphereRadius(5.f);
    SetRootComponent(SphereComponent);

}

void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}
