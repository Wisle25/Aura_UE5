// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /* Tag Container */);

UCLASS()
class UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// ***===== Lifecycles? =====*** //

	void AbilitySystemOnSet();

	FEffectAssetTags EffectAssetTags;

protected:

	// ***===== Effects =====*** //

	void AffectApplied(UAbilitySystemComponent* AbilitySystem, const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle Handler);
};
