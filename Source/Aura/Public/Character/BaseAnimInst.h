// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInst.generated.h"

class ACharacterBase;
class UCharacterMovementComponent;

UCLASS()
class AURA_API UBaseAnimInst : public UAnimInstance
{
	GENERATED_BODY()

public:
	// ***===== Lifecycles =====*** //

	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;	

protected:
	// ***===== References =====*** //

	UPROPERTY()
	TWeakObjectPtr<ACharacterBase> Character;

	UPROPERTY()
	TWeakObjectPtr<UCharacterMovementComponent> Movement;

	// ***===== Locomotion =====*** //

	UPROPERTY(BlueprintReadOnly, Category=Locomotion)
	float GroundSpeed;

	void GetLocomotionData();
};
