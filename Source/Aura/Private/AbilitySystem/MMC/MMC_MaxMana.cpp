// Copyright, Wisle25


#include "AbilitySystem/MMC/MMC_MaxMana.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interfaces/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
    // Max mana is derived from Intelligence, thats why we're getting Intelligence
    IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
    IntelligenceDef.AttributeSource    = EGameplayEffectAttributeCaptureSource::Target;
    IntelligenceDef.bSnapshot          = false;

    RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const 
{
    // Gather tags from source and target
    const FGameplayTagContainer* SourceTag = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTag = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParams;
    EvaluationParams.SourceTags = SourceTag;
    EvaluationParams.TargetTags = TargetTag;

    float Intelligence = 0.f;
    GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluationParams, Intelligence);
    Intelligence = FMath::Max(Intelligence, 0.f);

    // Finally set the max health
    ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());

    return 50.f + 2.5f * Intelligence + 15.f * CombatInterface->GetLevel();
}
