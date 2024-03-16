// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class IEnemyInterface;

UCLASS()
class AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();

	// ***===== Lifecycles =====*** //

	virtual void PlayerTick(float DeltaTime) override;

protected:
	// ***===== Lifecycles =====*** //

	virtual void BeginPlay() override;	

private:
	void AssetInitializer();

	// ***===== Input =====*** //

	UPROPERTY(EditDefaultsOnly, Category=Input)
	TSoftObjectPtr<UInputMappingContext> InputContext;

	void UseInputContext();

	// ***===== Enemy Interaction =====*** //

	IEnemyInterface* CurrentEnemy;
	IEnemyInterface* LastEnemy;

	void CursorTrace();
};
