// Copyright, Wisle25

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AuraGameplayTags.h"

void UAuraAbilitySystemComponent::AbilitySystemOnSet()
{
    const FAuraGameplayTags& Tags = FAuraGameplayTags::Get();
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("Native Tag: %s"), *Tags.Attributes_Secondary_Armor.ToString()));

    // Bind delegate
    OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::AffectApplied);
}

void UAuraAbilitySystemComponent::AffectApplied(UAbilitySystemComponent* AbilitySystem, const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle Handler)
{
    FGameplayTagContainer TagContainer;
    Spec.GetAllAssetTags(TagContainer);

    EffectAssetTags.Broadcast(TagContainer);
}
