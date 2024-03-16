// Copyright, Wisle25

#include "Game/AuraGameModeBase.h"
#include "GameFramework/PlayerState.h"

AAuraGameModeBase::AAuraGameModeBase()
{
    // ...    
    AssetInitializer();
}

void AAuraGameModeBase::AssetInitializer()
{
    // *** Default Class *** //

    static ConstructorHelpers::FClassFinder<APawn> PawnAsset(
        TEXT("/Game/Blueprints/Character/Player/BP_PlayerCharacter")
    );
    DefaultPawnClass = PawnAsset.Class;

    static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerAsset(
        TEXT("/Script/Aura.AuraPlayerController")
    );
    PlayerControllerClass = PlayerControllerAsset.Class;

    static ConstructorHelpers::FClassFinder<APlayerState> PlayerStateAsset(
        TEXT("/Script/Aura.AuraPlayerState")
    );
    PlayerStateClass = PlayerStateAsset.Class;
}
