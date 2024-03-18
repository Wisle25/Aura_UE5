// Copyright, Wisle25

#include "UI/Overlay/AuraOverlay.h"
#include "Controller/WidgetController/OverlayWidgetController.h"
#include "UI/ProgressGlobe/ProgressGlobeBase.h"

//////////////////////////////////////////////////////////
// ==================== Lifecycles ==================== //

void UAuraOverlay::NativeConstruct()
{
    Super::NativeConstruct();

    BindEvents();
}

///////////////////////////////////////////////////////
// ==================== Widgets ==================== //

void UAuraOverlay::BindEvents()
{
    if (UOverlayWidgetController* OverlayController = Cast<UOverlayWidgetController>(WidgetController))
    {
        OverlayController->OnHealthChanged.AddUObject(HealthGlobe, &UProgressGlobeBase::SetPercentage);
    }
}
