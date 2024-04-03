// Copyright, Wisle25

#include "AbilitySystem/AuraAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{

}

//////////////////////////////////////////////////////////
// ==================== Lifecycles ==================== //

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // * Vital Attributes * //
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);

    // * Primary Attributes * //
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strength, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Vigor, COND_None, REPNOTIFY_Always);

    // * Secondary Attributes * //
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Armor, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArmorPen, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CritChance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CritDamage, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CritRes, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthRegen, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaRegen, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    FEffectProperties EffectProperties;
    SetEffectProperties(Data, EffectProperties);

    // Basically just do clamping    
    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
        SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
    if (Data.EvaluatedData.Attribute == GetManaAttribute())
        SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
}

////////////////////////////////////////////////////////////////
// ==================== Vital Attributes ==================== //

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

//////////////////////////////////////////////////////////////////
// ==================== Primary Attributes ==================== //

void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldStrength);
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldIntelligence);
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resilience, OldResilience);
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Vigor, OldVigor);
}

//////////////////////////////////////////////////////////////////
// ==================== Primary Attributes ==================== //

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Armor, OldArmor);
}

void UAuraAttributeSet::OnRep_ArmorPen(const FGameplayAttributeData& OldArmorPen)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArmorPen, OldArmorPen);
}

void UAuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BlockChance, OldBlockChance);
}

void UAuraAttributeSet::OnRep_CritChance(const FGameplayAttributeData& OldCritChance)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CritChance, OldCritChance);
}

void UAuraAttributeSet::OnRep_CritDamage(const FGameplayAttributeData& OldCritDamage)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CritDamage, OldCritDamage);
}

void UAuraAttributeSet::OnRep_CritRes(const FGameplayAttributeData& OldCritRes)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CritRes, OldCritRes);
}

void UAuraAttributeSet::OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthRegen, OldHealthRegen);
}

void UAuraAttributeSet::OnRep_ManaRegen(const FGameplayAttributeData& OldManaRegen)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaRegen, OldManaRegen);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
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
