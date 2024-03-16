// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;
struct FInputActionValue;

UCLASS()
class APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	// ***===== Lifecycles =====*** //

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

private:
	void AssetInitializer();

	// ***===== Components =====*** //

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	// ***===== Input =====*** //

	UPROPERTY(EditDefaultsOnly, Category=Input)
	TSoftObjectPtr<UInputAction> MoveAction;

	// ***===== Locomotion =====*** //

	void Move(const FInputActionValue& InputValue);
};
