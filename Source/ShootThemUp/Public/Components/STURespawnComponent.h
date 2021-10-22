#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STURespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTURespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTURespawnComponent();

    void Respawn(const int32& RespawnTimer);

    FORCEINLINE int32 GetRespawnCountDown() const {return RespawnCountDown;};
    bool IsRespawnInProcess() const;

protected:
    FTimerHandle RespawnTimeHandle;
    int32 RespawnCountDown;

    void RespawnTimerUpdate();
};
