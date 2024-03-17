// Copyright, Wisle25

#include "UI/WidgetController/WidgetController.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UWidgetController::InitReferences(const FWidgetControllerParams& Params)
{
    PlayerController = Params.PlayerController;
    PlayerState 	 = Params.PlayerState;
    AbilitySystem    = Params.AbilitySystem;
    AttributeSet     = Params.AttributeSet;
}
