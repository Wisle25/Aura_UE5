// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UOverlayWidgetController;

UCLASS()
class UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UOverlayWidgetController* GetOverlayController(const UObject* WorldCtxObj);
};
