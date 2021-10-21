// Shoot Them Up. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_CouldBeTaken.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API UEnvQueryTest_CouldBeTaken : public UEnvQueryTest
{
	GENERATED_BODY()

public:
    UEnvQueryTest_CouldBeTaken();

    virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
