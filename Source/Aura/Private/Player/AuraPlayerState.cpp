// Copyright, Wisle25

#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

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

//////////////////////////////////////////////////////////
// ==================== Lifecycles ==================== //

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AAuraPlayerState, Level);    
}

//////////////////////////////////////////////////////////
// ==================== Attributes ==================== //

void AAuraPlayerState::OnRep_Level(int32 OldLevel)
{
    
}
