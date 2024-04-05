// Copyright, Wisle25

#include "AuraAssetManager.h"
#include "AuraGameplayTags.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
    check(GEngine);
    return *Cast<UAuraAssetManager>(GEngine->AssetManager);
}

void UAuraAssetManager::StartInitialLoading()
{
    Super::StartInitialLoading();

    FAuraGameplayTags::InitNativeGameplayTags();
}
