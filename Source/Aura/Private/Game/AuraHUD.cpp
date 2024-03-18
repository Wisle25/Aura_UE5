// Copyright, Wisle25

#include "Game/AuraHUD.h"
#include "UI/Overlay/AuraOverlay.h"
#include "Controller/WidgetController/OverlayWidgetController.h"

AAuraHUD::AAuraHUD()
{
    // ...
    AssetInitializer();
}

void AAuraHUD::AssetInitializer()
{
    // *** Overlay HUD *** //
    static ConstructorHelpers::FClassFinder<UAuraOverlay> OverlayWidgetAsset(
        TEXT("/Game/Blueprints/UI/Overlay/WBP_Overlay")
    );
    OverlayWidgetClass = OverlayWidgetAsset.Class;

    static ConstructorHelpers::FClassFinder<UOverlayWidgetController> OverlayWidgetControllerAsset(
        TEXT("/Script/Aura.OverlayWidgetController")
    );
    OverlayWidgetControllerClass = OverlayWidgetControllerAsset.Class;
}

///////////////////////////////////////////////////////////
// ==================== Overlay HUD ==================== //

void AAuraHUD::InitOverlay(const FWidgetControllerParams& WCParams)
{
    checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is not set!"))
    checkf(OverlayWidgetClass, TEXT("OverlayWidgeClass is not set!"))

    // Controller
    OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
    OverlayWidgetController->InitReferences(WCParams);
    OverlayWidgetController->BindOnChanges();

    // Widget
    OverlayWidget = CreateWidget<UAuraOverlay>(GetOwningPlayerController(), OverlayWidgetClass);
    OverlayWidget->SetWidgetController(OverlayWidgetController);
    OverlayWidget->AddToViewport();

    // Broadcast the initial values
    OverlayWidgetController->BroadcastInitialValues();
}
