// Copyright, Wisle25

#include "AbilitySystem/AuraAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
    InitHealth(25.f);
    InitMaxHealth(100.f);
    InitMana(10.f);
    InitMaxMana(50.f);
}

//////////////////////////////////////////////////////////
// ==================== Lifecycles ==================== //

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    // Basically just do clamping    
    if (Attribute == GetHealthAttribute())
        NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
    if (Attribute == GetManaAttribute())
        NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    FEffectProperties EffectProperties;
    SetEffectProperties(Data, EffectProperties);
}

//////////////////////////////////////////////////////////
// ==================== Primary Attributes ==================== //

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}

//////////////////////////////////////////////////////////
// ==================== Properties ==================== //

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
    // Source
    FGameplayEffectContextHandle SourceContext = Data.EffectSpec.GetContext();
    Props.EffectCtxHandle = SourceContext;
    Props.Source.AbilitySystem    = SourceContext.GetOriginalInstigatorAbilitySystemComponent();
    Props.Source.AvatarActor      = Props.Source.AbilitySystem->AbilityActorInfo->AvatarActor;
    if (APawn* Pawn = Cast<APawn>(Props.Source.AvatarActor.Get()))
    {
        Props.Source.AvatarController = Pawn->GetController();
    }

    // Target
    Props.Target.AbilitySystem    = Data.Target.AbilityActorInfo->AbilitySystemComponent;
    Props.Target.AvatarActor      = Props.Target.AbilitySystem->GetAvatarActor();
    if (APawn* Pawn = Cast<APawn>(Props.Target.AvatarActor.Get()))
    {
        Props.Target.AvatarController = Pawn->GetController();
    }
}
