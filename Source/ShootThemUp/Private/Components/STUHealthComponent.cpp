// Shoot Them Up. All rights reserved.


#include "STUHealthComponent.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComp, All, Log);

USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

    MaxHealth = 100.f;

    bAutoHeal = true;
    HealUpdateTime = 0.5f;
    HealDelay = 3.f;
    HealModifier = 1.f;
    
}

bool USTUHealthComponent::TryToAddHealth(const float& HealthAmount)
{
    if(Health == MaxHealth || IsDeath()) return false;

    SetHealth(FMath::Clamp(Health+HealthAmount, 0.f, MaxHealth));
    return true;
}


void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
    checkf(MaxHealth > 0, TEXT("Wrong USTUHealthComponent::MaxHealth parameter"));
    
    SetHealth(MaxHealth);
    AActor* OwnerActor = GetOwner();
    if(OwnerActor)
    {
        OwnerActor->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }
}

void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
    AController* InstigatedBy, AActor* DamageCauser)
{
    if(Damage <= 0.f || IsDeath() || !GetWorld()) return;
    
    SetHealth(Health - Damage);

    GetWorld()->GetTimerManager().ClearTimer(HealTimer);
    
    if(IsDeath())
    {
        OnDeath.Broadcast();
    }
    else if (bAutoHeal)
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimer, this,&USTUHealthComponent::HealUpdate,
          HealUpdateTime,true, HealDelay);  
    }
}

void USTUHealthComponent::HealUpdate()
{
    SetHealth(Health + HealModifier);
    
    if(FMath::IsNearlyEqual(Health,MaxHealth) && GetWorld()) GetWorld()->GetTimerManager().ClearTimer(HealTimer);
}

void USTUHealthComponent::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}
