// Copyright, Wisle25

#include "UI/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

AAuraHUD::AAuraHUD()
{
    // ...
    AssetInitializer();
}

void AAuraHUD::AssetInitializer()
{
    // *** Overlay HUD *** //
    static ConstructorHelpers::FClassFinder<UAuraUserWidget> OverlayWidgetAsset(
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
    // Controller
    OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
    OverlayWidgetController->InitReferences(WCParams);

    // Widget
    OverlayWidget = CreateWidget<UAuraUserWidget>(GetOwningPlayerController(), OverlayWidgetClass);
    OverlayWidget->AddToViewport();
    OverlayWidget->SetWidgetController(OverlayWidgetController);
}
