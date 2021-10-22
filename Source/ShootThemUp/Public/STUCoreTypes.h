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

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmpty, ASTUBaseWeapon*);

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
    UTexture2D* MainIcon = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    UTexture2D* CrossHairIcon = nullptr;
};

/** Health Component **/

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, float);

/** Anim Notify **/

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifySignature, USkeletalMeshComponent*);

/** Weapon Fx Component **/

class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FDecalData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UMaterialInterface* Decal;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FVector Size = FVector(10.f);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    float LifeTime = 5.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    float FadeOutTime = 0.7f;
};

USTRUCT(BlueprintType)
struct FImpactData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* NiagaraEffect;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FDecalData DecalData;
};

/** GameMode **/
USTRUCT(BlueprintType)
struct FGameData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
    int32 PlayersNum = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
    int32 RoundsNum = 4;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game", meta = (ClampMin = "1", ClampMax = "300"))
    int32 RoundTime = 10; // Seconds

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game")
    FLinearColor DefaultTeamColor = FLinearColor::Red;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game")
    TArray<FLinearColor> TeamColors;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game", meta = (ClampMin = "1", ClampMax = "20"))
    int32 RespawnTime = 5;
};

USTRUCT(BlueprintType)
struct FRoundData
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoundData")
    int32 RoundsNum = 0;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoundData")
    int32 CurrentRound = 1;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoundData")
    int32 RoundCountDown = 0;
};

/** PlayerState **/

USTRUCT(BlueprintType)
struct FPlayerStatistic
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerState")
    int32 KillsNum = 0;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerState")
    int32 DeathsNum = 0;
};



