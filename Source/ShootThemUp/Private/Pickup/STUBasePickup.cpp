// Shoot Them Up. All rights reserved.


#include "Pickup/STUBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogPickup, All, Log);

ASTUBasePickup::ASTUBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

    SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    SphereCollision->InitSphereRadius(10.f);
    SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SphereCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
    SetRootComponent(SphereCollision);

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(GetRootComponent());

    RespawnTime = 5.f;
    RotationYaw = 1.f;
}

void ASTUBasePickup::BeginPlay()
{
	Super::BeginPlay();
	checkf(SphereCollision, TEXT("ASTUBasePickup::BeginPlay() SphereCollision in not valid"));
    checkf(Mesh, TEXT("ASTUBasePickup::BeginPlay() Mesh is not valid"));
    GenerateRotationYaw();
}

void ASTUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);
    const APawn* Pawn = Cast<APawn>(OtherActor);
    if(!Pawn) return;
    
    if(GivePickupTo(Pawn))
    {
       PickupWasTaken();
    }
}

void ASTUBasePickup::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    AddActorLocalRotation(FRotator(0.f,RotationYaw,0.f));
}

void ASTUBasePickup::PickupWasTaken()
{
    SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
    GetRootComponent()->SetVisibility(false, true);
    GenerateRotationYaw();
    
    GetWorld()->GetTimerManager().SetTimer(RespawnTimer, this, &ASTUBasePickup::Respawn, RespawnTime);
}

void ASTUBasePickup::Respawn() const
{
    SphereCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
    GetRootComponent()->SetVisibility(true, true);
}

bool ASTUBasePickup::GivePickupTo(const APawn* Pawn)
{
    return false;
}

void ASTUBasePickup::GenerateRotationYaw()
{
    const auto RandBool = FMath::RandBool();
    RandBool ? RotationYaw *= 1 : RotationYaw *= -1;
}
