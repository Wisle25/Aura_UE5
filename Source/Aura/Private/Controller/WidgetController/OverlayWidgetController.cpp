// Copyright, Wisle25

#include "Controller/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"

//////////////////////////////////////////////////////////
// ==================== References ==================== //

void UOverlayWidgetController::BroadcastInitialValues()
{
    // Get current
    float Health    = AttributeSet->GetHealth();
    float MaxHealth = AttributeSet->GetMaxHealth(); 
    float Mana      = AttributeSet->GetMana();
    float MaxMana   = AttributeSet->GetMaxMana();

    // Broadcast
    OnHealthChanged.Broadcast(Health, MaxHealth);
    OnManaChanged.Broadcast(Mana, MaxMana);
}

void UOverlayWidgetController::BindOnChanges()
{
    AbilitySystem->GetGameplayAttributeValueChangeDelegate(
        AttributeSet->GetHealthAttribute()
    ).AddUObject(this, &ThisClass::HealthChanged);

    AbilitySystem->GetGameplayAttributeValueChangeDelegate(
        AttributeSet->GetMaxHealthAttribute()
    ).AddUObject(this, &ThisClass::MaxHealthChanged);

    AbilitySystem->GetGameplayAttributeValueChangeDelegate(
        AttributeSet->GetManaAttribute()
    ).AddUObject(this, &ThisClass::ManaChanged);

    AbilitySystem->GetGameplayAttributeValueChangeDelegate(
        AttributeSet->GetMaxManaAttribute()
    ).AddUObject(this, &ThisClass::MaxManaChanged);
}

//////////////////////////////////////////////////////////////
// ==================== GAS Attributes ==================== //

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
    OnHealthChanged.Broadcast(Data.NewValue, AttributeSet->GetMaxHealth());
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
    OnHealthChanged.Broadcast(AttributeSet->GetHealth(), Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
    OnManaChanged.Broadcast(Data.NewValue, AttributeSet->GetMaxMana());
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
    OnManaChanged.Broadcast(AttributeSet->GetMana(), Data.NewValue);
}

