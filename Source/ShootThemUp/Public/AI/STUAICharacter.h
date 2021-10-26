// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/STUBaseCharacter.h"
#include "STUAICharacter.generated.h"

class UWidgetComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUAICharacter : public ASTUBaseCharacter
{
	GENERATED_BODY()

public:
    ASTUAICharacter(const FObjectInitializer& ObjectInitializer);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UWidgetComponent* HealthBarComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HealthBar")
    float HealthVisibilityDistance;
    
    virtual void OnHealthChanged(const float Health, const float HealthDelta) override;
    virtual void OnDeath() override;
    void UpdateHealthBar();
    virtual void Tick(float DeltaSeconds) override;
};
