// Shoot Them Up. All rights reserved.


#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"
#include "STUCoreTypes.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, Log);

// Sets default values
ASTUBaseWeapon::ASTUBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    SetRootComponent(Mesh);

    MuzzleSocketName = "MuzzleProjectileSocket";
    ShotMagnitude = 3000.0f;
    DefaultAmmo= {15,5,false};
}

void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(Mesh);
    checkf(DefaultAmmo.Bullets > 0, TEXT("Weapon %s has Bullets < 0. Please set >= 0;"), *GetName());
    checkf(DefaultAmmo.Clips > 0, TEXT("Weapon %s has Clips < 0. Please set >= 0;"), *GetName());
    
    CurrentAmmo = DefaultAmmo;
}

bool ASTUBaseWeapon::GetTraceData(FVector& StartPoint, FVector& EndPoint) const
{
    FVector ViewPointLocation;
    FRotator ViewPointRotation;
    
    if(!GetPlayerViewPoint(ViewPointLocation,ViewPointRotation)) return false;
    
    StartPoint = ViewPointLocation;
    EndPoint = StartPoint + ViewPointRotation.Vector() * ShotMagnitude;
    return true;
}

void ASTUBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& StartPoint, const FVector& EndPoint) const
{
    if(!GetWorld()) return;
    
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(GetOwner());
    
    GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint,ECC_Visibility, QueryParams);
}

APlayerController* ASTUBaseWeapon::GetPlayerController() const
{
    if(!GetOwner()) return nullptr;

    const auto Player = Cast<ACharacter>(GetOwner());
    return Player->GetController<APlayerController>();
}

bool ASTUBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const auto Controller = GetPlayerController();
    if(!Controller) return false;
    
    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    return true;
}

void ASTUBaseWeapon::DecreaseBullet()
{
    CurrentAmmo.Bullets--;
    if(IsClipEmpty())
    {
        OnClipEmpty.Broadcast(this);
    }
}

void ASTUBaseWeapon::ChangeClip()
{
    StopFire();
    if(IsAmmoEmpty() && !CurrentAmmo.Infinite) return;
    
    CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    CurrentAmmo.Clips--;
}

bool ASTUBaseWeapon::TryToAddAmmo(const int32& ClipsAmount)
{
    if(IsAmmoFull() || (CurrentAmmo.Infinite && CurrentAmmo.Bullets == DefaultAmmo.Bullets)) return false;
    if(IsAmmoEmpty())
    {
        CurrentAmmo.Clips = FMath::Clamp(ClipsAmount, 0, DefaultAmmo.Clips + 1);
        OnClipEmpty.Broadcast(this);
        return true;
    }
    else 
    {
        if(CurrentAmmo.Bullets != DefaultAmmo.Bullets) CurrentAmmo.Bullets = DefaultAmmo.Bullets; 
        CurrentAmmo.Clips = FMath::Clamp(CurrentAmmo.Clips + ClipsAmount, 0, DefaultAmmo.Clips);
        return true;
    }
}

