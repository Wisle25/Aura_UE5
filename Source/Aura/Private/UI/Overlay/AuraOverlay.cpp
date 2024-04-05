// Copyright, Wisle25

#include "UI/Overlay/AuraOverlay.h"
#include "Components/Button.h"
#include "Controller/WidgetController/OverlayWidgetController.h"
#include "Game/AuraHUD.h"
#include "UI/AttributeMenu/AttributeMenu.h"
#include "UI/Overlay/MessageWidget.h"
#include "UI/ButtonWidget.h"
#include "UI/ProgressGlobe/ProgressGlobeBase.h"

//////////////////////////////////////////////////////////
// ==================== Lifecycles ==================== //

void UAuraOverlay::NativeConstruct()
{
    Super::NativeConstruct();

    // ...
    BindEvents();
}

///////////////////////////////////////////////////////
// ==================== Widgets ==================== //

void UAuraOverlay::BindEvents()
{
    // ...
    if (UOverlayWidgetController* OverlayController = Cast<UOverlayWidgetController>(WidgetController))
    {
        OverlayController->OnHealthChanged.AddUObject(HealthGlobe, &UProgressGlobeBase::SetPercentage);
        OverlayController->OnManaChanged  .AddUObject(ManaGlobe, &UProgressGlobeBase::SetPercentage);
        OverlayController->MessageWidget.AddLambda([this](FUIWidgetRow Row) {
            MessageWidget->PrepareMessage(Row.Image.LoadSynchronous(), Row.Message);
        });
    }

    // Attributes
    AttrButton             ->Button->OnClicked.AddDynamic(this, &ThisClass::OpenAttributes);
    AuraHUD->AttributeMenu ->OnClose.AddLambda([this]() {
        AttrButton->Button->SetIsEnabled(true);
    });
}

//////////////////////////////////////////////////////
// ==================== Events ==================== //

void UAuraOverlay::OpenAttributes()
{
    AttrButton->Button->SetIsEnabled(false);
    AuraHUD   ->AttributeMenu->SetVisibility(ESlateVisibility::Visible);
}
