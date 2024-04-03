// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interfaces/CombatInterface.h"
#include "CharacterBase.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UCLASS(Abstract)
class ACharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	ACharacterBase();

protected:
	// ***===== Combat =====*** //

	UPROPERTY(VisibleAnywhere, Category=Combat)
	TObjectPtr<USkeletalMeshComponent> Weapon;

	// ***===== Attributes =====*** //

	UPROPERTY(EditAnywhere, Category=Attributes)
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(EditAnywhere, Category=Attributes)
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(EditAnywhere, Category=Attributes)
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	void ApplyEffectToSelf(const TSubclassOf<UGameplayEffect> EffectClass, float Level = 1.f) const;
	void InitDefaultAttributes() const;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override 
	{ 
		return nullptr;
	}
};
