// Shoot Them Up. All rights reserved.


#include "Components/STUWeaponComponent.h"
#include "GameFramework/Character.h"
#include "Notifies/STUEquipFinishedNotify.h"
#include "Weapon/STUBaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, Log);

USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

    EquipWeaponSocketName = "EquipWeaponSocket";
    SpareWeaponSocketName = "SpareWeaponSocket";

    CurrentWeaponIndex = 0;
    CurrentWeapon = nullptr;
    bEquipAnimInProgress = false;
}


void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
    SpawnWeapon();
    InitAnimations();
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
    if(!CanFire()) return;
    CurrentWeapon->StartFire();
}

void USTUWeaponComponent::StopFire() 
{
    if(!CanFire()) return;
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
    bEquipAnimInProgress = true;
    PlayAnimMontage(EquipMontage);
}

void USTUWeaponComponent::NextWeapon()
{
    if(!CanEquip()) return;
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* Montage) const
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if(!Character) return;

    Character->PlayAnimMontage(Montage);
}

void USTUWeaponComponent::InitAnimations()
{
    if(!EquipMontage) return;
    
    TArray<FAnimNotifyEvent> NotifiesEvents = EquipMontage->Notifies;
    for(auto Event : NotifiesEvents)
    {
        const auto EquipNotify = Cast<USTUEquipFinishedNotify>(Event.Notify);
        if(!EquipNotify) continue;
        EquipNotify->OnNotify.AddUObject(this,&USTUWeaponComponent::OnEquipFinished);
    }
}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* Mesh)
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if(!Character || Character->GetMesh() != Mesh) return;
    bEquipAnimInProgress = false;
}