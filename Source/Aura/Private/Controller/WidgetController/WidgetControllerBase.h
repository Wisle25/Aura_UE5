// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WidgetControllerBase.generated.h"

class AAuraPlayerController;
class AAuraPlayerState;
class UAuraAbilitySystemComponent;
class UAuraAttributeSet;

struct FWidgetControllerParams
{
	AAuraPlayerController* PlayerController;
	AAuraPlayerState* PlayerState;
	UAuraAbilitySystemComponent* AbilitySystem;
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
	virtual void BindOnChanges() {}

protected:
	// ***===== References =====*** //

	UPROPERTY()	
	TWeakObjectPtr<AAuraPlayerController> PlayerController;

	UPROPERTY()
	TWeakObjectPtr<AAuraPlayerState> PlayerState;

	UPROPERTY()
	TWeakObjectPtr<UAuraAbilitySystemComponent> AbilitySystem;

	UPROPERTY()
	TWeakObjectPtr<UAuraAttributeSet> AttributeSet;
};
