// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomExecutionCalculation.h"
#include "../AttributeSet/GAS_AttributeSet.h"



struct SDmageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalDamageCoefficient);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health)

	SDmageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGAS_AttributeSet, PhysicalDamage, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGAS_AttributeSet, PhysicalDamageCoefficient, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGAS_AttributeSet, Armor, Target, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGAS_AttributeSet, Health, Target, true);
	}
};

static const SDmageStatics& DamageStatics()
{
	static SDmageStatics DStatics;
	return DStatics;
}


UCustomExecutionCalculation::UCustomExecutionCalculation()
{
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalDamageCoefficientDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().HealthDef);
}
//BlueprintNativeEvent
void UCustomExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
															FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	OutExecutionOutput.MarkConditionalGameplayEffectsToTrigger();

	UAbilitySystemComponent* TargetAbilitySystem = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystem = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* TargetActor = TargetAbilitySystem ? TargetAbilitySystem->GetAvatarActor() : nullptr;
	AActor* SourceActor = SourceAbilitySystem ? SourceAbilitySystem->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Armor = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParameters, Armor);

	float Damage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().PhysicalDamageDef, EvaluationParameters, Damage);

	float DamageCoefficient = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().PhysicalDamageCoefficientDef, EvaluationParameters, DamageCoefficient);

	float UnmitigatedDamage = Damage * DamageCoefficient;

	float MitigatedDamage = UnmitigatedDamage - Armor;

	if (MitigatedDamage > 0.0f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(DamageStatics().HealthProperty, EGameplayModOp::Additive, -MitigatedDamage));

// 		OutExecutionOutput.AddOutputModifier(
// 			FGameplayModifierEvaluatedData(DamageStatics().ArmorProperty, EGameplayModOp::Additive, -10.0f));
	}
}

