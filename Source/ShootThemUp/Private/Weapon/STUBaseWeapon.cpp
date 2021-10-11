// Shoot Them Up. All rights reserved.


#include "Weapon/STUBaseWeapon.h"

// Sets default values
ASTUBaseWeapon::ASTUBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    SetRootComponent(Mesh);
}

void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}
