// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Character/CharacterBase.h"
#include "Interfaces/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

class UAbilitySystemComponent;
class UAuraAbilitySystemComponent;
class UAuraAttributeSet;

UCLASS()
class AEnemyCharacter : public ACharacterBase, public IEnemyInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();

	// ***===== Enemy Interaction =====*** //

	virtual void Highlight() override;
	virtual void UnHighlight() override;

protected:
	// ***==== Lifecycles =====*** //

	virtual void BeginPlay() override;

	// ***===== Ability System =====*** //

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystem;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAuraAttributeSet> AttributeSet;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
