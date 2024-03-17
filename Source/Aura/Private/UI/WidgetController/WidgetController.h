// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WidgetController.generated.h"

class AAuraPlayerController;
class AAuraPlayerState;
class UAbilitySystemComponent;
class UAttributeSet;

struct FWidgetControllerParams
{
	AAuraPlayerController* PlayerController;
	AAuraPlayerState* PlayerState;
	UAbilitySystemComponent* AbilitySystem;
	UAttributeSet* AttributeSet;
};

UCLASS()
class UWidgetController : public UObject
{
	GENERATED_BODY()

public:
	// ***===== References =====*** //

	void InitReferences(const FWidgetControllerParams& Params);

protected:
	// ***===== References =====*** //

	UPROPERTY()	
	TWeakObjectPtr<AAuraPlayerController> PlayerController;

	UPROPERTY()
	TWeakObjectPtr<AAuraPlayerState> PlayerState;

	UPROPERTY()
	TWeakObjectPtr<UAbilitySystemComponent> AbilitySystem;

	UPROPERTY()
	TWeakObjectPtr<UAttributeSet> AttributeSet;
};
