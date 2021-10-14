#pragma once

#include "STUCoreTypes.generated.h"

/** Base Charachter **/

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
    EMS_Normal   UMETA(DisplayName = "Normal"),
    EMS_Sprint   UMETA(DisplayName = "Sprint"),
 
    EMS_MAX      UMETA(DisplayName = "MaxDefault")
};

/** Weapon Component **/

class ASTUBaseWeapon;

USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    TSubclassOf<ASTUBaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    UAnimMontage* ReloadMontage = nullptr;
};

/** Base Weapon **/

DECLARE_MULTICAST_DELEGATE(FOnClipEmpty);

USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
    int32 Bullets;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
    int32 Clips;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
    bool Infinite;
};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    UTexture2D* MainIcon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    UTexture2D* CrossHairIcon;
};

/** Health Component **/

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);

/** Anim Notify **/

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifySignature, USkeletalMeshComponent*);