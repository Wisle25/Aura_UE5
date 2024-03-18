// Copyright, Wisle25

#include "Controller/WidgetController/WidgetControllerBase.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UWidgetControllerBase::InitReferences(const FWidgetControllerParams& Params)
{
    PlayerController = Params.PlayerController;
    PlayerState 	 = Params.PlayerState;
    AbilitySystem    = Params.AbilitySystem;
    AttributeSet     = Params.AttributeSet;
}
