// Shoot Them Up. All rights reserved.


#include "STUHealthComponent.h"

#include "STUFireDamageType.h"
#include "STUIceDamageType.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComp, All, Log);

USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
    Health = HealthMax;

    AActor* OwnerActor = GetOwner();
    if(OwnerActor)
    {
        OwnerActor->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }
}

void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
    AController* InstigatedBy, AActor* DamageCauser)
{
    UE_LOG(LogHealthComp, Display, TEXT("%s got %f Damage || Instigator - %s || Causer - %s"), *DamagedActor->GetName(),
        Damage, InstigatedBy ? *InstigatedBy->GetName() : *FString("Nullptr"), *DamageCauser->GetName());

    Health -= Damage;

    if(DamageType->IsA<USTUFireDamageType>())
    {
        UE_LOG(LogHealthComp, Display, TEXT("Fire DamageType"));
    }
    else if (DamageType->IsA<USTUIceDamageType>())
    {
        UE_LOG(LogHealthComp, Display, TEXT("Ice DamageType"));
    }
}
