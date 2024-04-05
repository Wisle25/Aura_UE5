// Copyright, Wisle25

#include "UI/AuraUserWidgetBase.h"
#include "Controller/WidgetController/WidgetControllerBase.h"
#include "Game/AuraHUD.h"
#include "Player/AuraPlayerController.h"

void UAuraUserWidgetBase::SetWidgetController(UWidgetControllerBase* InController)
{
    WidgetController = InController;
    
    if (APlayerController* PlayerController = InController->GetPlayerController())
    {
        AuraHUD          = Cast<AAuraHUD>(PlayerController->GetHUD());  
    }
}
