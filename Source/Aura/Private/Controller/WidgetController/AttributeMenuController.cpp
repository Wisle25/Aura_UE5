// Copyright, Wisle25

#include "Controller/WidgetController/AttributeMenuController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AuraGameplayTags.h"
#include "AttributeMenuController.h"

UAttributeMenuController::UAttributeMenuController()
{
    InitAsset();    
}

void UAttributeMenuController::InitAsset()
{
    static ConstructorHelpers::FObjectFinder<UAttributeInfo> AttributeInfoAsset(
        TEXT("/Script/Aura.AttributeInfo'/Game/Blueprints/AbilitySystem/Data/DA_AttributeInfo.DA_AttributeInfo'")
    );
    AttributeInfo = AttributeInfoAsset.Object;
}

////////////////////////////////////////////////////////////////////
// ==================== WidgetControllerBase ==================== //

void UAttributeMenuController::BroadcastInitialValues()
{
    check(AttributeInfo);

    for (auto& AttrInfo : AttributeSet->AttributeTags)
    {
        BroadcastAttributeInfo(AttrInfo.Key, AttrInfo.Value());
    }
}

void UAttributeMenuController::BindOnChanges()
{
    for (auto& AttrInfo : AttributeSet->AttributeTags)
    {
        AbilitySystem->GetGameplayAttributeValueChangeDelegate(AttrInfo.Value()).AddLambda(
            [&](const FOnAttributeChangeData& Data) {
                BroadcastAttributeInfo(AttrInfo.Key, AttrInfo.Value());
            }
        );
    }
}

void UAttributeMenuController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
    FAuraAttributeInfo Info = AttributeInfo->FindInfoForTag(AttributeTag);
    Info.AttributeValue = Attribute.GetNumericValue(AttributeSet.Get());

    AttributeOnChange.Broadcast(Info);
}
