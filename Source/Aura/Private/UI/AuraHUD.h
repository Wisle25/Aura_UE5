// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraUserWidget;
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
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	/** Initialize the controller and widget itself */
	void InitOverlay(const FWidgetControllerParams& WCParams);

private:
	void AssetInitializer();

	// ***===== Overlay HUD =====*** //

	UPROPERTY(EditDefaultsOnly, Category=OverlayHUD)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category=OverlayHUD)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
