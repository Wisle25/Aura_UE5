// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "UI/AuraUserWidgetBase.h"
#include "AuraOverlay.generated.h"

class UAttributeMenu;
class UButtonWidget;
class UMessageWidget;
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
	TObjectPtr<UProgressGlobeBase> ManaGlobe;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UMessageWidget> MessageWidget;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButtonWidget> AttrButton;

	void BindEvents();

	// ***===== Events =====*** //

	UFUNCTION()
	void OpenAttributes();
};
