// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "Controller/WidgetController/WidgetControllerBase.h"
#include "OverlayWidgetController.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, float);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnManaChanged, float, float);

struct FOnAttributeChangeData;

UCLASS()
class UOverlayWidgetController : public UWidgetControllerBase
{
	GENERATED_BODY()

public:
	// ***===== References =====*** //

	virtual void BroadcastInitialValues() override;
	virtual void BindOnChanges() override;

	// ***===== GAS Attributes =====*** //

	// ** Health ** //
	FOnHealthChanged OnHealthChanged;

	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;

	// ** Mana ** //

	FOnManaChanged OnManaChanged;

	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;
};
