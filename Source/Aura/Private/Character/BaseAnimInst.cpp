// Copyright, Wisle25

#include "Character/BaseAnimInst.h"
#include "Character/CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

//////////////////////////////////////////////////////////
// ==================== Lifecycles ==================== //

void UBaseAnimInst::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    Character = Cast<ACharacterBase>(TryGetPawnOwner());
    if (Character.IsValid())
        Movement  = Character->GetCharacterMovement();
}

void UBaseAnimInst::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

    if (!Movement.IsValid()) return;

    GetLocomotionData();
}

//////////////////////////////////////////////////////////
// ==================== Locomotion ==================== //

void UBaseAnimInst::GetLocomotionData()
{
    GroundSpeed = Movement->Velocity.Size2D();
}
