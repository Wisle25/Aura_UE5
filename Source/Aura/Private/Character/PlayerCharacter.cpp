// Copyright, Wisle25

#include "Character/PlayerCharacter.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Camera/CameraComponent.h"
#include "Game/AuraHUD.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "Controller/WidgetController/WidgetControllerBase.h"

#include "EnhancedInputComponent.h"
#include "PlayerCharacter.h"

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

void APlayerCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    // ...
    InitPlayerReference(NewController);
    InitAbilitySystem();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* Input)
{
    Super::SetupPlayerInputComponent(Input);

    UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(Input);

    EnhancedInput->BindAction(MoveAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &ThisClass::Move);
}

//////////////////////////////////////////////////////////
// ==================== References ==================== //

void APlayerCharacter::InitPlayerReference(AController *NewController)
{
    // Getting reference
    AuraPlayerController = Cast<AAuraPlayerController>(NewController);
    AuraPlayerState = GetPlayerState<AAuraPlayerState>();
}

void APlayerCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    InitPlayerReference(GetController());
    InitAbilitySystem();
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

//////////////////////////////////////////////////////////////
// ==================== Ability System ==================== //

void APlayerCharacter::InitAbilitySystem()
{
    // ...
    if (AuraPlayerState.IsValid())
        AuraPlayerState->GetAbilitySystem()->InitAbilityActorInfo(AuraPlayerState.Get(), this);

    // Init Overlay HUD
    if (AuraPlayerController.IsValid())
    {
        if (AAuraHUD* HUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
        {
            HUD->InitOverlay({ AuraPlayerController.Get(), AuraPlayerState.Get(), AuraPlayerState->GetAbilitySystem(), AuraPlayerState->GetAttributeSet() });
        }
    }
}

UAbilitySystemComponent* APlayerCharacter::GetAbilitySystemComponent() const 
{
    return AuraPlayerState->GetAbilitySystem();
}
