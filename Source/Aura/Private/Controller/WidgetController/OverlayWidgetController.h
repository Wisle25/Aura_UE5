// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "Controller/WidgetController/WidgetControllerBase.h"
#include "OverlayWidgetController.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, float);

UCLASS()
class UOverlayWidgetController : public UWidgetControllerBase
{
	GENERATED_BODY()

public:
	// ***===== References =====*** //

	virtual void BroadcastInitialValues() override;

	// ***===== GAS Attributes =====*** //

	FOnHealthChanged OnHealthChanged;
};
