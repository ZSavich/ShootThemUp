// Shoot Them Up. All rights reserved.


#include "Weapon/STUBaseWeapon.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
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
    
    DamageAmount = 15.f;
    DamageType = UDamageType::StaticClass();
    FireRate = 0.1f;
    FireScatter = 0.025f;
}

void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(Mesh);
}

void ASTUBaseWeapon::StartFire()
{
    GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &ASTUBaseWeapon::MakeShot, FireRate, true);
}

void ASTUBaseWeapon::StopFire()
{
    GetWorld()->GetTimerManager().ClearTimer(FireTimer);
}

void ASTUBaseWeapon::MakeShot()
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

bool ASTUBaseWeapon::GetTraceData(FVector& StartPoint, FVector& EndPoint) const
{
    FVector ViewPointLocation;
    FRotator ViewPointRotation;
    
    if(!GetPlayerViewPoint(ViewPointLocation,ViewPointRotation)) return false;
    
    StartPoint = ViewPointLocation;
    const auto Scatter = FMath::VRandCone(ViewPointRotation.Vector(), FireScatter);
    EndPoint = StartPoint + Scatter * ShotMagnitude;
    return true;
}

void ASTUBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& StartPoint, const FVector& EndPoint) const
{
    if(!GetWorld()) return;
    
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(GetOwner());
    
    GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint,ECC_Visibility, QueryParams);
}

void ASTUBaseWeapon::MakeDamage(AActor* const TargetActor)
{   
    if(!TargetActor || !TargetActor->IsA<ACharacter>()) return;
    UGameplayStatics::ApplyDamage(TargetActor,DamageAmount,GetPlayerController(),this, DamageType);
}



