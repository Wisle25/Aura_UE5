// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectInfo
{
	GENERATED_BODY()

	UPROPERTY()
	TWeakObjectPtr<UAbilitySystemComponent> AbilitySystem;

	UPROPERTY()
	TWeakObjectPtr<AActor> AvatarActor;

	UPROPERTY()
	TWeakObjectPtr<AController> AvatarController;
};

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	UPROPERTY()
	FGameplayEffectContextHandle EffectCtxHandle;

	UPROPERTY()
	FEffectInfo Source;

	UPROPERTY()
	FEffectInfo Target;
};

UCLASS()
class UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UAuraAttributeSet();

	// ***===== Lifecycles =====*** //

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// ***===== Vital Attributes =====*** //

	/** Health */
	UPROPERTY(ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	/** Mana */
	UPROPERTY(ReplicatedUsing=OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	// ***===== Primary Attributes =====*** //

	UPROPERTY(ReplicatedUsing=OnRep_Strength)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength);

	UPROPERTY(ReplicatedUsing=OnRep_Intelligence)
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence);

	UPROPERTY(ReplicatedUsing=OnRep_Resilience)
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience);

	UPROPERTY(ReplicatedUsing=OnRep_Vigor)
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor);

	// ***===== Secondary Attributes =====*** //

	UPROPERTY(ReplicatedUsing=OnRep_Armor)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor);

	UPROPERTY(ReplicatedUsing=OnRep_ArmorPen)
	FGameplayAttributeData ArmorPen;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPen);

	UFUNCTION()
	void OnRep_ArmorPen(const FGameplayAttributeData& OldArmorPen);

	UPROPERTY(ReplicatedUsing=OnRep_BlockChance)
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);

	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance);

	UPROPERTY(ReplicatedUsing=OnRep_CritChance)
	FGameplayAttributeData CritChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CritChance);

	UFUNCTION()
	void OnRep_CritChance(const FGameplayAttributeData& OldCritChance);

	UPROPERTY(ReplicatedUsing=OnRep_CritDamage)
	FGameplayAttributeData CritDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CritDamage);

	UFUNCTION()
	void OnRep_CritDamage(const FGameplayAttributeData& OldCritDamage);

	UPROPERTY(ReplicatedUsing=OnRep_CritRes)
	FGameplayAttributeData CritRes;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CritRes);

	UFUNCTION()
	void OnRep_CritRes(const FGameplayAttributeData& OldCritRes);

	UPROPERTY(ReplicatedUsing=OnRep_HealthRegen)
	FGameplayAttributeData HealthRegen;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegen);

	UFUNCTION()
	void OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen);

	UPROPERTY(ReplicatedUsing=OnRep_ManaRegen)
	FGameplayAttributeData ManaRegen;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegen);

	UFUNCTION()
	void OnRep_ManaRegen(const FGameplayAttributeData& OldManaRegen);

	/** Max Health */
	UPROPERTY(ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	/** Max Mana */
	UPROPERTY(ReplicatedUsing=OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

private:
	// ***===== Properties =====*** //

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
