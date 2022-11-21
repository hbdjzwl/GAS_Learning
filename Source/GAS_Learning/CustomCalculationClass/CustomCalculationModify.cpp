// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCalculationModify.h"
#include "GameplayEffectExecutionCalculation.h"
#include "../AttributeSet/GAS_AttributeSet.h"


//
//�ο�����:https://blog.csdn.net/m0_38110586/article/details/116181067
// 
// 
// #define DECLARE_ATTRIBUTE_CAPTUREDEF(P) \
// 	FProperty* P##Property; \
// 	FGameplayEffectAttributeCaptureDefinition P##Def; \
// 
// #define DEFINE_ATTRIBUTE_CAPTUREDEF(S, P, T, B) \
// { \
// 	P##Property = FindFieldChecked<FProperty>(S::StaticClass(), GET_MEMBER_NAME_CHECKED(S, P)); \
// 	P##Def = FGameplayEffectAttributeCaptureDefinition(P##Property, EGameplayEffectAttributeCaptureSource::T, B); \
// }



/* ע��˴���S��P�������������ŵ�AttributeSet���Ӧ�еĳ�Ա */
struct SDamageStatics
{
	//FGameplayEffectAttributeCaptureDefinition ����
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);

	SDamageStatics()
	{
		//��DamagePropertyָ�븳ֵ���ҹ���һ��FGameplayEffectAttributeCaptureDefinition����
		//����:��Ҫ�ǻ�ȡUAttributeSetBase��Damage
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGAS_AttributeSet, PhysicalDamage, Source, true);
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, Armor, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGAS_AttributeSet, Armor, Target, true);
	}
};

static const SDamageStatics& DamageStatics()
{
	static SDamageStatics DStatics;
	return DStatics;
}

UCustomCalculationModify::UCustomCalculationModify()
{

	//�����û����MMC�Ĺ��캯���н�FGameplayEffectAttributeCaptureDefinition��ӵ�RelevantAttributesToCapture��
	//���ҳ��Բ���Attribute, ��ô����õ�һ�����ڲ���ʱȱʧSpec�Ĵ���. �������Ҫ����Attribute, ��ô�Ͳ������ʲ
	//ô��RelevantAttributesToCapture.
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	//��������:TArray<FGameplayEffectAttributeCaptureDefinition> RelevantAttributesToCapture;
}


float UCustomCalculationModify::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//Spec.GetContext().GetInstigatorAbilitySystemComponent();
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Damage = 0.0f;
	GetCapturedAttributeMagnitude(DamageStatics().PhysicalDamageDef, Spec, EvaluationParameters, Damage);

	float Armor = 0.0f;
	GetCapturedAttributeMagnitude(DamageStatics().ArmorDef, Spec, EvaluationParameters, Armor);


	return Damage - Armor;
}

