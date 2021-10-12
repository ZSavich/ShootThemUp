// Shoot Them Up. All rights reserved.


#include "Weapon/STUBaseWeapon.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, Log);

// Sets default values
ASTUBaseWeapon::ASTUBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    SetRootComponent(Mesh);

    MuzzleSocketName = "MuzzleProjectileSocket";
    ShotMagnitude = 1500.0f;
}

void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(Mesh);
}

void ASTUBaseWeapon::Fire()
{
    MakeShot();
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



