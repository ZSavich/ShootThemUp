// Shoot Them Up. All rights reserved.


#include "Components/STUWeaponComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/STUBaseWeapon.h"

USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

    SnapToSocketName = "WeaponSocket";
}


void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
    SpawnWeapon();
}

void USTUWeaponComponent::Fire()
{
    if(!CurrentWeapon) return;
    CurrentWeapon->Fire();
}

void USTUWeaponComponent::SpawnWeapon()
{
    if(!GetWorld() || !WeaponClass || !GetOwner()) return;
    const ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
    
    if(!OwnerCharacter) return;
    
    CurrentWeapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
    
    if(!CurrentWeapon) return;
    
    const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    CurrentWeapon->AttachToComponent(OwnerCharacter->GetMesh(), AttachmentRules, SnapToSocketName);
}
