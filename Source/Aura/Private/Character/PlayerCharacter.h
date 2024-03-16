// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Character/CharacterBase.h"
#include "PlayerCharacter.generated.h"

class AAuraPlayerState;
class UCameraComponent;
class USpringArmComponent;
class UInputAction;
struct FInputActionValue;

UCLASS()
class APlayerCharacter : public ACharacterBase, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	// ***===== Lifecycles =====*** //

	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

private:
	void AssetInitializer();

	// ***===== References =====*** //

	UPROPERTY()
	TWeakObjectPtr<AAuraPlayerState> AuraPlayerState;

	virtual void OnRep_PlayerState() override;

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

	// ***===== Ability System =====*** //

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
