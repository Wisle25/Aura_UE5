// Copyright, Wisle25

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Game/AuraHUD.h"
#include "Player/AuraPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Controller/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayController(const UObject* WorldCtxObj)
{
    AAuraPlayerController* PC = Cast<AAuraPlayerController>(UGameplayStatics::GetPlayerController(WorldCtxObj, 0));    

    if (!PC) return nullptr;

    if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
        return AuraHUD->OverlayWidgetController;

    return nullptr;
}
