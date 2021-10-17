// Shoot Them Up. All rights reserved.


#include "Weapon/STURifleWeapon.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "STUWeaponFXComponent.h"

ASTURifleWeapon::ASTURifleWeapon()
{
    WeaponFX = CreateDefaultSubobject<USTUWeaponFXComponent>(TEXT("WeaponFXComponent"));
    FireRate = 0.1f;
    FireScatter = 0.025f;
    
    DamageAmount = 15.f;
}

void ASTURifleWeapon::BeginPlay()
{
    Super::BeginPlay();
    checkf(WeaponFX, TEXT("ASTURifleWeapon WeaponFX is Not Valid!"));
}

void ASTURifleWeapon::StartFire()
{    
    GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &ASTUBaseWeapon::MakeShot, FireRate, true, 0.f);
}

void ASTURifleWeapon::StopFire()
{
    GetWorld()->GetTimerManager().ClearTimer(FireTimer);
}

void ASTURifleWeapon::MakeShot()
{
    if(!GetWorld() || IsAmmoEmpty())
    {
        StopFire();
        return;
    }
    
    FVector StartPoint, EndPoint;
    if(!GetTraceData(StartPoint,EndPoint))
    {
        StopFire();
        return;
    }

    FHitResult HitResult;
    MakeHit(HitResult, StartPoint, EndPoint);
        
    if(HitResult.bBlockingHit)
    {
        MakeDamage(HitResult.GetActor());
        //DrawDebugLine(GetWorld(), GetMuzzleWorldLocation() , HitResult.ImpactPoint, FColor::Red,false,5.f);
        //DrawDebugSphere(GetWorld(), HitResult.ImpactPoint,10.f,24.f,FColor::Red,false,5.f);
        WeaponFX->PlayImpactFX(HitResult);
    } else
    {
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation() , EndPoint, FColor::Red,false,5.f);
    }
    DecreaseBullet();
}

bool ASTURifleWeapon::GetTraceData(FVector& StartPoint, FVector& EndPoint) const
{
    FVector ViewPointLocation;
    FRotator ViewPointRotation;
    
    if(!GetPlayerViewPoint(ViewPointLocation,ViewPointRotation)) return false;
    
    StartPoint = ViewPointLocation;
    const auto Scatter = FMath::VRandCone(ViewPointRotation.Vector(), FireScatter);
    EndPoint = StartPoint + Scatter * ShotMagnitude;
    return true;
}

void ASTURifleWeapon::MakeDamage(AActor* const TargetActor)
{   
    if(!TargetActor || !TargetActor->IsA<ACharacter>()) return;
    UGameplayStatics::ApplyDamage(TargetActor,DamageAmount,GetPlayerController(),this, UDamageType::StaticClass());
}
