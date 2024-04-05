// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/** Singleton gameplay tags containing native gameplay tags */
struct FAuraGameplayTags
{
public:
	FORCEINLINE static const FAuraGameplayTags& Get()
	{
		return GameplayTags;
	}
	
	static void InitNativeGameplayTags();

	// ***===== Actual Tags =====*** //

	// * Primary Attribute * //

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;

	// * Secondary Attribute * //

	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPen;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CritChance;
	FGameplayTag Attributes_Secondary_CritDamage;
	FGameplayTag Attributes_Secondary_CritRes;
	FGameplayTag Attributes_Secondary_HealthRegen;
	FGameplayTag Attributes_Secondary_ManaRegen;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;

private:
	static FAuraGameplayTags GameplayTags;
};
