// Shoot Them Up. All rights reserved.


#include "Weapon/STUBaseWeapon.h"
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
}

void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(Mesh);
}

void ASTUBaseWeapon::StartFire()
{}

void ASTUBaseWeapon::StopFire()
{}

void ASTUBaseWeapon::MakeShot()
{}

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



