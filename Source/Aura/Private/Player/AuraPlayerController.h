// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;

UCLASS()
class AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();

protected:
	// ***===== Lifecycles =====*** //

	virtual void BeginPlay() override;	

private:
	void AssetInitializer();

	// ***===== Input =====*** //

	UPROPERTY(EditDefaultsOnly, Category=Input)
	TSoftObjectPtr<UInputMappingContext> InputContext;

	void UseInputContext();
};
