// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "GameFramework/PlayerController.h"
#include "STUPlayerController.generated.h"

class USTURespawnComponent;
UCLASS()
class SHOOTTHEMUP_API ASTUPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    ASTUPlayerController();
    
    virtual void BeginPlay() override;
    virtual void OnPossess(APawn* InPawn) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USTURespawnComponent* RespawnComponent;

    virtual void SetupInputComponent() override;

    void OnPauseGame();
    void OnMatchStateChanged(const EMatchState State);
};
