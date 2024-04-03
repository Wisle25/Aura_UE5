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

	// ***===== Lifecycles =====*** //

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// ***===== Ability System =====*** //

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystem;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAuraAttributeSet> AttributeSet;

private:
	// ***===== Attributes =====*** //

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level, Category=Attributes)
	int32 Level = 1;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

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
	FORCEINLINE int32 GetPlayerLevel() const
	{
		return Level;
	}
};
