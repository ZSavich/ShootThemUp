// Shoot Them Up. All rights reserved.


#include "Components/STUWeaponComponent.h"
#include "GameFramework/Character.h"
#include "Notifies/STUEquipFinishedNotify.h"
#include "Notifies/STUReloadFinishedNotify.h"
#include "Weapon/STUBaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, Log);

USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

    EquipWeaponSocketName = "EquipWeaponSocket";
    SpareWeaponSocketName = "SpareWeaponSocket";

    CurrentWeaponIndex = 0;
    CurrentWeapon = nullptr;
    CurrentReloadMontage = nullptr;
    bEquipAnimInProgress = false;
    bReloadAnimInProgress = false;
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
    CurrentReloadMontage = nullptr;
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
    if(!GetWorld() || !WeaponData.Num() || !Character) return;

    for(auto OneWeaponData : WeaponData)
    {
        const auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(OneWeaponData.WeaponClass);
        if(!Weapon) continue;
        Weapons.Add(Weapon);
        AttachWeaponToSocket(Weapon, Character->GetMesh(), SpareWeaponSocketName);
        Weapon->OnClipEmpty.AddUObject(this, &USTUWeaponComponent::OnClipEmpty);
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
    const auto CurrentWeaponData = WeaponData.FindByPredicate(
        [&](const FWeaponData& Data){return Data.WeaponClass == CurrentWeapon->GetClass();}
    );
    
    CurrentReloadMontage = CurrentWeaponData ? CurrentWeaponData->ReloadMontage : CurrentReloadMontage;
    
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
    const auto EquipNotify = FindNotifyByMontage<USTUEquipFinishedNotify>(EquipMontage);
    if(EquipNotify)
    {
        EquipNotify->OnNotify.AddUObject(this,&USTUWeaponComponent::OnEquipFinished);
    }
    
    for(const auto OneWeaponData: WeaponData)
    {
        const auto ReloadNotify = FindNotifyByMontage<USTUReloadFinishedNotify>(OneWeaponData.ReloadMontage);
        if(!ReloadNotify) continue;
        ReloadNotify->OnNotify.AddUObject(this, &USTUWeaponComponent::OnReloadFinished);
    }
}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* Mesh)
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if(!Character || Character->GetMesh() != Mesh) return;
    bEquipAnimInProgress = false;
}

void USTUWeaponComponent::OnReloadFinished(USkeletalMeshComponent* Mesh)
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if(!Character || Character->GetMesh() != Mesh) return;
    CurrentWeapon->ChangeClip();
    bReloadAnimInProgress = false;
}

void USTUWeaponComponent::OnClipEmpty()
{
    CurrentWeapon->StopFire();
    Reload();
}

void USTUWeaponComponent::Reload()
{    
    if(!CanReload() || !CurrentWeapon->CanReload()) return;
    
    bReloadAnimInProgress = true;
    PlayAnimMontage(CurrentReloadMontage);
}

template <typename T>
T* USTUWeaponComponent::FindNotifyByMontage(const UAnimMontage* Montage)
{
    if(!Montage) return nullptr;
    
    const auto NotifiesEvents = Montage->Notifies;
    for(auto Event : NotifiesEvents)
    {
        const auto Notify = Cast<T>(Event.Notify);
        if(Notify) return Notify;
    }
    return nullptr;
}
