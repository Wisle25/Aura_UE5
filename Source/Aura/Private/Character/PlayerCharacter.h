// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "PlayerCharacter.generated.h"

class AAuraPlayerController;
class AAuraPlayerState;
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

    virtual void PossessedBy(AController *NewController) override;
    virtual void SetupPlayerInputComponent(UInputComponent *InputComponent) override;

	// ***===== Combat Interface =====*** //

	FORCEINLINE int32 GetLevel() const;

private:
    void AssetInitializer();

    // ***===== References =====*** //

	UPROPERTY()
	TWeakObjectPtr<AAuraPlayerController> AuraPlayerController;

	UPROPERTY()
	TWeakObjectPtr<AAuraPlayerState> AuraPlayerState;

	/** For player state, player controller, etc */
    void InitPlayerReference();

	/** Client version of "PossesedBy" */
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

	void InitAbilitySystem();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
