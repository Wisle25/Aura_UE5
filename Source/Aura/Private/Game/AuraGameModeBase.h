// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"

UCLASS()
class AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAuraGameModeBase();

private:
	void AssetInitializer();	
};
