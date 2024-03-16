// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

class IEnemyInterface
{
	GENERATED_BODY()

public:
	// ***===== Enemy Interaction =====*** //

	virtual void Highlight() = 0;
	virtual void UnHighlight() = 0;
};
