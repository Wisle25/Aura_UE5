// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAuraAbilitySystemComponent;
class UAuraAttributeSet;

UCLASS()
class AAuraPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AAuraPlayerState();

protected:
	// ***===== Ability System =====*** //

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystem;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAuraAttributeSet> AttributeSet;

public:
	// ***===== Accessors =====*** //
	FORCEINLINE UAuraAbilitySystemComponent* GetAbilitySystem() const
	{
		return AbilitySystem;
	}
	FORCEINLINE UAuraAttributeSet* GetAttributeSet() const
	{
		return AttributeSet;
	}
};
