// Copyright, Wisle25

#include "Player/AuraPlayerController.h"
#include "Interfaces/EnemyInterface.h"

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

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);

    CursorTrace();    
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

///////////////////////////////////////////////////////////
// ==================== Enemy Interaction ==================== //

void AAuraPlayerController::CursorTrace()
{
    FHitResult HitResult;
    GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

    if (!HitResult.bBlockingHit) return;

    LastEnemy = CurrentEnemy;
    CurrentEnemy = Cast<IEnemyInterface>(HitResult.GetActor());

    // Highlight the enemy
    if (!LastEnemy && CurrentEnemy)
        CurrentEnemy->Highlight();
    else if (LastEnemy && !CurrentEnemy)
    {
        LastEnemy->UnHighlight();
    }
    else if (LastEnemy != CurrentEnemy)
    {
        LastEnemy   ->UnHighlight();
        CurrentEnemy->Highlight();
    }
}
