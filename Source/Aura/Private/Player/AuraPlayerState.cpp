// Copyright, Wisle25

#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
    NetUpdateFrequency = 100.f;

    // Ability System
    AbilitySystem = CreateDefaultSubobject<UAuraAbilitySystemComponent>("Ability System");
    AbilitySystem->SetIsReplicated(true);
    AbilitySystem->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

    // Attribute Set
    AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("Attribute Set");
}
