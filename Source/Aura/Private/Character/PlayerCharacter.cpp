// Copyright, Wisle25

#include "Character/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "EnhancedInputComponent.h"

APlayerCharacter::APlayerCharacter()
{
    bUseControllerRotationYaw = bUseControllerRotationPitch = bUseControllerRotationRoll = false;

    // Movement
    GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->bConstrainToPlane         = true;
    GetCharacterMovement()->bSnapToPlaneAtStart       = true;

    // Spring Arm
    SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->bEnableCameraLag = true;
    SpringArm->bInheritPitch = SpringArm->bInheritRoll = SpringArm->bInheritYaw = false;
    
    // Camera
    Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    Camera->SetupAttachment(SpringArm);

    // ...
    AssetInitializer();    
}

void APlayerCharacter::AssetInitializer()
{
    // *** Input *** //

    static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionAsset(
        TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_MoveAction.IA_MoveAction'")
    );
    MoveAction = MoveActionAsset.Object;
}

//////////////////////////////////////////////////////////
// ==================== Lifecycles ==================== //

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* Input)
{
    Super::SetupPlayerInputComponent(Input);

    UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(Input);

    EnhancedInput->BindAction(MoveAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &ThisClass::Move);
}

//////////////////////////////////////////////////////////
// ==================== Locomotion ==================== //

void APlayerCharacter::Move(const FInputActionValue& InputValue)
{
    const FVector2D Value = InputValue.Get<FVector2D>();

    FRotator ControlRotation = GetControlRotation();

    // Get forward and right vector
    FRotationMatrix RotationMatrix = FRotationMatrix(ControlRotation);
    FVector Forward = RotationMatrix.GetUnitAxis(EAxis::X);
    FVector Right   = RotationMatrix.GetUnitAxis(EAxis::Y);

    // Apply
    AddMovementInput(Forward, Value.Y);
    AddMovementInput(Right, Value.X);
}

