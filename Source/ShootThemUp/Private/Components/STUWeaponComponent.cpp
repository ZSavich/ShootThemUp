// Shoot Them Up. All rights reserved.


#include "Components/STUWeaponComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/STUBaseWeapon.h"

USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

    EquipWeaponSocketName = "EquipWeaponSocket";
    SpareWeaponSocketName = "SpareWeaponSocket";

    CurrentWeaponIndex = 0;
    CurrentWeapon = nullptr;
}


void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
    SpawnWeapon();
    EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;
    for(const auto Weapon: Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();
    Super::EndPlay(EndPlayReason);
}

void USTUWeaponComponent::StartFire()
{
    if(!CurrentWeapon) return;
    CurrentWeapon->StartFire();
}

void USTUWeaponComponent::StopFire()
{
    if(!CurrentWeapon) return;
    CurrentWeapon->StopFire();
}

void USTUWeaponComponent::SpawnWeapon()
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if(!GetWorld() || !WeaponClasses.Num() || !Character) return;

    for(auto WeaponClass : WeaponClasses)
    {
        const auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
        if(!Weapon) continue;
        Weapons.Add(Weapon);
        AttachWeaponToSocket(Weapon, Character->GetMesh(), SpareWeaponSocketName);
    }
}

void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* Component, const FName& SocketName) const
{
    if(!Weapon || !Component) return;
    const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(Component, AttachmentRules, SocketName);
    Weapon->SetOwner(GetOwner());
}

void USTUWeaponComponent::EquipWeapon(const int32 WeaponIndex)
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if(!Weapons.IsValidIndex(WeaponIndex) || !Character) return;
    
    if(CurrentWeapon)
    {
        StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), SpareWeaponSocketName);
    }
    CurrentWeapon = Weapons[WeaponIndex];
    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), EquipWeaponSocketName);
}

void USTUWeaponComponent::NextWeapon()
{
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}
