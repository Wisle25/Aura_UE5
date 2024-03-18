// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "UI/AuraUserWidgetBase.h"
#include "AuraOverlay.generated.h"

class UProgressGlobeBase;

UCLASS()
class UAuraOverlay : public UAuraUserWidgetBase
{
	GENERATED_BODY()

protected:
	// ***===== Lifecycles =====*** //

	virtual void NativeConstruct() override;

	// ***===== Widgets =====*** //

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressGlobeBase> HealthGlobe;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressGlobeBase> MannaGlobe;

	void BindEvents();
};
