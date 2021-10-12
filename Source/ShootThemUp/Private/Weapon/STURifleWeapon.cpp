// Shoot Them Up. All rights reserved.


#include "Weapon/STURifleWeapon.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ASTURifleWeapon::ASTURifleWeapon()
{
    FireRate = 0.1f;
    FireScatter = 0.025f;
    
    DamageAmount = 15.f;
}

void ASTURifleWeapon::StartFire()
{
    GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &ASTUBaseWeapon::MakeShot, FireRate, true);
}

void ASTURifleWeapon::StopFire()
{
    GetWorld()->GetTimerManager().ClearTimer(FireTimer);
}

void ASTURifleWeapon::MakeShot()
{
    if(!GetWorld()) return;
    
    FVector StartPoint, EndPoint;
    if(!GetTraceData(StartPoint,EndPoint)) return;

    FHitResult HitResult;
    MakeHit(HitResult, StartPoint, EndPoint);
        
    if(HitResult.bBlockingHit)
    {
        MakeDamage(HitResult.GetActor());
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation() , HitResult.ImpactPoint, FColor::Red,false,5.f);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint,10.f,24.f,FColor::Red,false,5.f);
        UE_LOG(LogTemp, Display, TEXT("Hited BoneName: %s"), *HitResult.BoneName.ToString());
    } else
    {
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation() , EndPoint, FColor::Red,false,5.f);
    }
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
