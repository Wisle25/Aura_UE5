// Copyright, Wisle25

#include "AbilitySystem/MMC/MMC_MaxHealth.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interfaces/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
    // Max health is derived from Vigor attribute, thats why we're getting it here
    VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
    VigorDef.AttributeSource    = EGameplayEffectAttributeCaptureSource::Target;
    VigorDef.bSnapshot          = false;

    RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const 
{
    // Gather tags from source and target
    const FGameplayTagContainer* SourceTag = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTag = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParams;
    EvaluationParams.SourceTags = SourceTag;
    EvaluationParams.TargetTags = TargetTag;

    float Vigor = 0.f;
    GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluationParams, Vigor);
    Vigor = FMath::Max(Vigor, 0.f);

    // Finally set the max health
    ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());

    return 80.f + 2.5f * Vigor + 10.f * CombatInterface->GetLevel();
}
