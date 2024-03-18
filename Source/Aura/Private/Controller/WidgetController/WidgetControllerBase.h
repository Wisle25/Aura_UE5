// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WidgetControllerBase.generated.h"

class AAuraPlayerController;
class AAuraPlayerState;
class UAbilitySystemComponent;
class UAuraAttributeSet;

struct FWidgetControllerParams
{
	AAuraPlayerController* PlayerController;
	AAuraPlayerState* PlayerState;
	UAbilitySystemComponent* AbilitySystem;
	UAuraAttributeSet* AttributeSet;
};

UCLASS()
class UWidgetControllerBase : public UObject
{
	GENERATED_BODY()

public:
	// ***===== References =====*** //

	void InitReferences(const FWidgetControllerParams& Params);

	virtual void BroadcastInitialValues() {}

protected:
	// ***===== References =====*** //

	UPROPERTY()	
	TWeakObjectPtr<AAuraPlayerController> PlayerController;

	UPROPERTY()
	TWeakObjectPtr<AAuraPlayerState> PlayerState;

	UPROPERTY()
	TWeakObjectPtr<UAbilitySystemComponent> AbilitySystem;

	UPROPERTY()
	TWeakObjectPtr<UAuraAttributeSet> AttributeSet;
};
