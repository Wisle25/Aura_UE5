// Copyright, Wisle25

#include "Game/AuraHUD.h"
#include "Controller/WidgetController/AttributeMenuController.h"
#include "Controller/WidgetController/OverlayWidgetController.h"
#include "UI/Overlay/AuraOverlay.h"
#include "UI/AttributeMenu/AttributeMenu.h"

AAuraHUD::AAuraHUD()
{
    // ...
    AssetInitializer();
}

void AAuraHUD::AssetInitializer()
{
    // * Overlay HUD * //
    static ConstructorHelpers::FClassFinder<UAuraOverlay> OverlayWidgetAsset(
        TEXT("/Game/Blueprints/UI/Overlay/WBP_Overlay")
    );
    OverlayWidgetClass = OverlayWidgetAsset.Class;

    static ConstructorHelpers::FClassFinder<UOverlayWidgetController> OverlayWidgetControllerAsset(
        TEXT("/Script/Aura.OverlayWidgetController")
    );
    OverlayWidgetControllerClass = OverlayWidgetControllerAsset.Class;

    // * Attribute HUD * //

    static ConstructorHelpers::FClassFinder<UAttributeMenu> AttributeMenuAsset(
        TEXT("/Game/Blueprints/UI/AttributeMenu/WBP_AttributeMenu")
    );
    AttributeMenuClass = AttributeMenuAsset.Class;


    static ConstructorHelpers::FClassFinder<UAttributeMenuController> AttributeMenuControllerAsset(
        TEXT("/Script/Aura.AttributeMenuController")
    );
    AttributeControllerClass = AttributeMenuControllerAsset.Class;
}

///////////////////////////////////////////////////////////
// ==================== Overlay HUD ==================== //

void AAuraHUD::InitHUD(const FWidgetControllerParams& WCParams)
{
    checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is not set!"))
    checkf(OverlayWidgetClass, TEXT("OverlayWidgeClass is not set!"))
    checkf(AttributeControllerClass, TEXT("OverlayWidgeClass is not set!"))
    checkf(AttributeMenuClass, TEXT("AttrMenu is not set!"))

    // Controller
    OverlayWidgetController = CreateController<UOverlayWidgetController>(WCParams, OverlayWidgetControllerClass);
    AttributeMenuController = CreateController<UAttributeMenuController>(WCParams, AttributeControllerClass);

    // Widget
    AttributeMenu = CreateHUD<UAttributeMenu>(AttributeMenuClass, AttributeMenuController, false);
    OverlayWidget = CreateHUD<UAuraOverlay>(OverlayWidgetClass, OverlayWidgetController);

    /** We want draw attribute menu ontop of overlay widget */
    AttributeMenu->AddToViewport();

    // Broadcast the initial values
    AttributeMenuController->BroadcastInitialValues();
    OverlayWidgetController->BroadcastInitialValues();
}
