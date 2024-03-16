// Copyright, Wisle25

#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

AAuraPlayerController::AAuraPlayerController()
{
    bReplicates = true;

    // ...
    AssetInitializer();
}

void AAuraPlayerController::AssetInitializer()
{
    static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputContextAsset(
        TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Inputs/IMC_MainContext.IMC_MainContext'")
    );
    InputContext = InputContextAsset.Object;
}

//////////////////////////////////////////////////////////
// ==================== Lifecycles ==================== //

void AAuraPlayerController::BeginPlay()
{
    Super::BeginPlay();

    UseInputContext();
}

/////////////////////////////////////////////////////
// ==================== Input ==================== //

void AAuraPlayerController::UseInputContext()
{
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->ClearAllMappings();
        Subsystem->AddMappingContext(InputContext.LoadSynchronous(), 0);
    }

    // Mouse Cursor
    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Default;

    /* Input Mode */
    FInputModeGameAndUI InputModeData;
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    InputModeData.SetHideCursorDuringCapture(false);

    SetInputMode(InputModeData);
}
