// Shoot Them Up. All rights reserved.


#include "Weapon/STURifleWeapon.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "STUWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

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
    InitMuzzleFX();
    GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &ASTUBaseWeapon::MakeShot, FireRate, true, 0.f);
}

void ASTURifleWeapon::StopFire()
{
    SetMuzzleFXVisible(false);
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
        MakeDamage(HitResult.GetActor());
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

void ASTURifleWeapon::MakeDamage(AActor* const TargetActor)
{
    if(!TargetActor || !TargetActor->IsA<ACharacter>()) return;
    UGameplayStatics::ApplyDamage(TargetActor,DamageAmount, GetController(),this, UDamageType::StaticClass());
}

void ASTURifleWeapon::InitMuzzleFX()
{
    if(!MuzzleEffectComponent)
    {
        MuzzleEffectComponent = SpawnMuzzleFX();
    }
    SetMuzzleFXVisible(true);
}

void ASTURifleWeapon::SetMuzzleFXVisible(const bool Visibility) const
{
    if(!MuzzleEffectComponent) return;
    MuzzleEffectComponent->SetPaused(!Visibility);
    MuzzleEffectComponent->SetVisibility(Visibility, true);
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