// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraOverlay;
class UAttributeMenu;
class UAttributeMenuController;
class UOverlayWidgetController;
class UWidgetControllerBase;
struct FWidgetControllerParams;

UCLASS()
class AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	AAuraHUD();

	/** Initialize the controller and widget itself */
	void InitHUD(const FWidgetControllerParams& WCParams);

	// ***===== Overlay HUD =====*** //

	UPROPERTY()
	TObjectPtr<UAuraOverlay> OverlayWidget;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	// ***===== Attribute Menu =====*** //
	
	UPROPERTY()
	TObjectPtr<UAttributeMenu> AttributeMenu;

	UPROPERTY()
	TObjectPtr<UAttributeMenuController> AttributeMenuController;

private:
	void AssetInitializer();

	template <typename T>
	T* CreateController(const FWidgetControllerParams& WCParams, TSubclassOf<T> ControllerClass)
	{
		T* NewController = NewObject<T>(this, ControllerClass);
		NewController->InitReferences(WCParams);
		NewController->BindOnChanges();

		return NewController;
	}

	template <typename T>
	T* CreateHUD(TSubclassOf<T> HUDClass, UWidgetControllerBase* HUDController, bool bImmediateAdd /* to viewport */ = true)
	{
		T* NewHUD = CreateWidget<T>(GetOwningPlayerController(), HUDClass);
		NewHUD->SetWidgetController(HUDController);

		if (bImmediateAdd)
			NewHUD->AddToViewport();

		return NewHUD;
	}

	// ***===== Overlay HUD =====*** //

	UPROPERTY(EditDefaultsOnly, Category=OverlayHUD)
	TSubclassOf<UAuraOverlay> OverlayWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category=OverlayHUD)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	// ***===== Attribute Menu =====*** //

	UPROPERTY(EditDefaultsOnly, Category=AttributeHUD)
	TSubclassOf<UAttributeMenu> AttributeMenuClass;

	UPROPERTY(EditDefaultsOnly, Category=AttributeMenu)
	TSubclassOf<UAttributeMenuController> AttributeControllerClass;
};
