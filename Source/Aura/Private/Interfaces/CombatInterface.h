// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ICombatInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetLevel() const
	{
		return 0;
	}
};
