// Shoot Them Up. All rights reserved.


#include "Components/STUWeaponComponent.h"
#include "GameFramework/Character.h"
#include "Notifies/STUEquipFinishedNotify.h"
#include "Notifies/STUReloadFinishedNotify.h"
#include "Weapon/STUBaseWeapon.h"
#include "Notifies/AnimUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, Log);

constexpr static int32 WeaponDataCount = 2;

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
    bCanFire = true;
}


void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
    checkf(WeaponData.Num() == WeaponDataCount, TEXT("WeaponComponent mush has 2 weapons!"));
    
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
        Zoom(false);
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
    const auto EquipNotify = AnimUtils::FindNotifyByMontage<USTUEquipFinishedNotify>(EquipMontage);
    if(EquipNotify)
    {
        EquipNotify->OnNotify.AddUObject(this,&USTUWeaponComponent::OnEquipFinished);
    }
    else
    {
        UE_LOG(LogWeaponComponent, Error, TEXT("EquipAnimation doesn't have any EquipNotifies!"));
        checkNoEntry();
    }
    
    for(const auto OneWeaponData: WeaponData)
    {
        const auto ReloadNotify = AnimUtils::FindNotifyByMontage<USTUReloadFinishedNotify>(OneWeaponData.ReloadMontage);
        if(!ReloadNotify)
        {
            UE_LOG(LogWeaponComponent, Error,
                TEXT("ReloadAnimation for %s doesn't have any ReloadNotifies!"), *OneWeaponData.WeaponClass->GetName());
            checkNoEntry();
            continue;
        }
        ReloadNotify->OnNotify.AddUObject(this, &USTUWeaponComponent::OnReloadFinished);
    }
}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* Mesh)
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if(!Character || Character->GetMesh() != Mesh) return;
    bEquipAnimInProgress = false;
    if(CurrentWeapon->IsClipEmpty() && !CurrentWeapon->IsAmmoEmpty())
    {
        Reload();
    }
}

void USTUWeaponComponent::OnReloadFinished(USkeletalMeshComponent* Mesh)
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if(!Character || Character->GetMesh() != Mesh) return;
    CurrentWeapon->ChangeClip();
    bReloadAnimInProgress = false;
    bCanFire = true;
}

void USTUWeaponComponent::OnClipEmpty(ASTUBaseWeapon* TriggerWeapon)
{
    if(CurrentWeapon->GetClass() != TriggerWeapon->GetClass()) return;
    CurrentWeapon->StopFire();
    Reload();
}

void USTUWeaponComponent::Reload()
{    
    if(!CanReload() || !CurrentWeapon->CanReload()) return;
    StopFire();
    bReloadAnimInProgress = true;
    PlayAnimMontage(CurrentReloadMontage);
}

bool USTUWeaponComponent::GetWeaponUIData (FWeaponUIData& UIData) const
{
    if(!CurrentWeapon) return false;
    UIData = CurrentWeapon->GetUIData();
    return true;
}

bool USTUWeaponComponent::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
    if(!CurrentWeapon) return false;
    AmmoData = CurrentWeapon->GetWeaponAmmo();
    return true;
}

bool USTUWeaponComponent::TryToAddAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType, const int32 ClipsAmount) 
{
    for(const auto Weapon: Weapons)
    {
        if(Weapon && Weapon->IsA(WeaponType))
        {
            return Weapon->TryToAddAmmo(ClipsAmount);
        }
    }
    return false;
}

void USTUWeaponComponent::Zoom(const bool bState)
{
    CurrentWeapon->Zoom(bState);
}
