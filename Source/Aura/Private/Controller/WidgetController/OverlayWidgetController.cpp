// Copyright, Wisle25

#include "Controller/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"

UOverlayWidgetController::UOverlayWidgetController()
{
    // Init Data
    static ConstructorHelpers::FObjectFinder<UDataTable> DataAsset(
        TEXT("/Script/Engine.DataTable'/Game/Blueprints/UI/Data/DT_MessageWidget.DT_MessageWidget'")
    );
    MessageWidgetData = DataAsset.Object;
}

//////////////////////////////////////////////////////////
// ==================== References ==================== //

void UOverlayWidgetController::BroadcastInitialValues()
{
    // Get current
    float Health    = AttributeSet->GetHealth();
    float MaxHealth = AttributeSet->GetMaxHealth(); 
    float Mana      = AttributeSet->GetMana();
    float MaxMana   = AttributeSet->GetMaxMana();

    // Broadcast
    OnHealthChanged.Broadcast(Health, MaxHealth);
    OnManaChanged.Broadcast(Mana, MaxMana);
}

void UOverlayWidgetController::BindOnChanges()
{
    AbilitySystem->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute())
        .AddLambda([this](const FOnAttributeChangeData& Data) {
            OnHealthChanged.Broadcast(Data.NewValue, AttributeSet->GetMaxHealth());
        });

    AbilitySystem->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute())
        .AddLambda([this](const FOnAttributeChangeData& Data) {
            OnHealthChanged.Broadcast(AttributeSet->GetHealth(), Data.NewValue);
        });

    AbilitySystem->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetManaAttribute())
        .AddLambda([this](const FOnAttributeChangeData& Data) {
            OnManaChanged.Broadcast(Data.NewValue, AttributeSet->GetMaxMana());
        });

    AbilitySystem->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxManaAttribute())
        .AddLambda([this](const FOnAttributeChangeData& Data) {
            OnManaChanged.Broadcast(AttributeSet->GetMana(), Data.NewValue);
        });

    AbilitySystem->EffectAssetTags.AddLambda(
        [this](const FGameplayTagContainer& TagContainer) {
            // Check on the config file is the tag exists
            FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag("Message");

            for (const auto& Tag : TagContainer)
            {
                if (!Tag.MatchesTag(MessageTag)) continue;

                const FUIWidgetRow* Row = MessageWidgetData->FindRow<FUIWidgetRow>(Tag.GetTagName(), TEXT(""));
                MessageWidget.Broadcast(*Row);
            }
        }
    );
}
