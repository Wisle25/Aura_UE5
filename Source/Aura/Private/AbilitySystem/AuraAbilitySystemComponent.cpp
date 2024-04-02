// Copyright, Wisle25

#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilitySystemOnSet()
{
    // Bind delegate
    OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::AffectApplied);
}

void UAuraAbilitySystemComponent::AffectApplied(UAbilitySystemComponent* AbilitySystem, const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle Handler)
{
    FGameplayTagContainer TagContainer;
    Spec.GetAllAssetTags(TagContainer);

    EffectAssetTags.Broadcast(TagContainer);
}
