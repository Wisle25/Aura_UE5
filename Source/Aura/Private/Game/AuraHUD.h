// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraOverlay;
class UOverlayWidgetController;
struct FWidgetControllerParams;

UCLASS()
class AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	AAuraHUD();

	// ***===== Overlay HUD =====*** //

	UPROPERTY()
	TObjectPtr<UAuraOverlay> OverlayWidget;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	/** Initialize the controller and widget itself */
	void InitOverlay(const FWidgetControllerParams& WCParams);

private:
	void AssetInitializer();

	// ***===== Overlay HUD =====*** //

	UPROPERTY(EditDefaultsOnly, Category=OverlayHUD)
	TSubclassOf<UAuraOverlay> OverlayWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category=OverlayHUD)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
