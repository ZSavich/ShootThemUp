// Shoot Them Up. All rights reserved.


#include "Weapon/STURifleWeapon.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "STUWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

ASTURifleWeapon::ASTURifleWeapon()
{
    WeaponFX = CreateDefaultSubobject<USTUWeaponFXComponent>(TEXT("WeaponFXComponent"));
    FireRate = 0.1f;
    FireScatter = 0.025f;
    DamageAmount = 15.f;
    TraceTargetName = "TraceTarget";
}

void ASTURifleWeapon::BeginPlay()
{
    Super::BeginPlay();
    checkf(WeaponFX, TEXT("ASTURifleWeapon WeaponFX is Not Valid!"));
}

void ASTURifleWeapon::StartFire()
{
    InitFX();
    GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &ASTUBaseWeapon::MakeShot, FireRate, true, 0.f);
}

void ASTURifleWeapon::StopFire()
{
    SetFXVisible(false);
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

    FVector EndTarget = EndPoint;
    
    if(HitResult.bBlockingHit)
    {
        EndTarget = HitResult.ImpactPoint;
        MakeDamage(HitResult);
        WeaponFX->PlayImpactFX(HitResult);
    }
    DecreaseBullet();
    SpawnTraceFX(GetMuzzleWorldLocation(), EndTarget);
}

bool ASTURifleWeapon::GetTraceData(FVector& StartPoint, FVector& EndPoint) const
{
    FVector ViewPointLocation;
    FRotator ViewPointRotation;
    
    if(!GetCharacterViewPoint(ViewPointLocation,ViewPointRotation)) return false;
    
    StartPoint = ViewPointLocation;
    const auto Scatter = FMath::VRandCone(ViewPointRotation.Vector(), FireScatter);
    EndPoint = StartPoint + Scatter * ShotMagnitude;
    return true;
}

void ASTURifleWeapon::Zoom(const bool bState)
{
    const auto Controller = Cast<APlayerController>(GetController());
    if(!Controller || !Controller->PlayerCameraManager) return;
    if(bState)
    {
        FOVDefaultZoom = Controller->PlayerCameraManager->GetFOVAngle();
    }
    
    Controller->PlayerCameraManager->SetFOV(bState ? FOVZoomAngle : FOVDefaultZoom);
}

void ASTURifleWeapon::MakeDamage(const FHitResult& HitResult)
{
    //UGameplayStatics::ApplyDamage(HitResult.GetActor(),DamageAmount, GetController(),this, UDamageType::StaticClass());
    UGameplayStatics::ApplyPointDamage(HitResult.GetActor(),DamageAmount,FVector::ZeroVector,
        HitResult,GetController(),this,UDamageType::StaticClass());
    
}

void ASTURifleWeapon::InitFX()
{
    if(!MuzzleEffectComponent)
        MuzzleEffectComponent = SpawnMuzzleFX();
    if(!ShootAudioComponent)
        ShootAudioComponent = UGameplayStatics::SpawnSoundAttached(ShootSound, Mesh, MuzzleSocketName,
            FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget,
            false,1,1,0,nullptr,nullptr,
            false);
            
    SetFXVisible(true);
}

void ASTURifleWeapon::SetFXVisible(const bool isActive) const
{
    if(!MuzzleEffectComponent) return;
    MuzzleEffectComponent->SetPaused(!isActive);
    MuzzleEffectComponent->SetVisibility(isActive, true);
    if(!ShootAudioComponent) return;
    isActive ? ShootAudioComponent->Play() : ShootAudioComponent->Stop();
}

void ASTURifleWeapon::SpawnTraceFX(const FVector StartTarget, const FVector EndTarget) const
{
    if(!TraceEffect) return;
    const auto TraceEffectComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceEffect,
        StartTarget);
    if(TraceEffectComponent)
    {
        TraceEffectComponent->SetVariableVec3(TraceTargetName, EndTarget);
    }
}

AController* ASTURifleWeapon::GetController() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    return Player ? Player->GetController() : nullptr;
}