// Copyright, Wisle25

#include "Controller/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"

// ==================== References ==================== //

void UOverlayWidgetController::BroadcastInitialValues()
{
    // Get current
    float Health    = AttributeSet->GetHealth();
    float MaxHealth = AttributeSet->GetMaxHealth(); 

    // Broadcast
    OnHealthChanged.Broadcast(Health, MaxHealth);
}
