// Shoot Them Up. All rights reserved.


#include "STUHealthComponent.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComp, All, Log);

USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
    Health = MaxHealth;

    AActor* OwnerActor = GetOwner();
    if(OwnerActor)
    {
        OwnerActor->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }
}

void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
    AController* InstigatedBy, AActor* DamageCauser)
{
    if(Damage <= 0.f || IsDeath()) return;
    
    Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
    
    OnHealthChanged.Broadcast(Health);
    if(IsDeath()) OnDeath.Broadcast();
}
