// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCalculationModify.h"
#include "GameplayEffectExecutionCalculation.h"
#include "../AttributeSet/GAS_AttributeSet.h"


//
//参考链接:https://blog.csdn.net/m0_38110586/article/details/116181067
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



/* 注意此处的S和P参数必须是我门的AttributeSet类对应有的成员 */
struct SDamageStatics
{
	//FGameplayEffectAttributeCaptureDefinition 定义
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);

	SDamageStatics()
	{
		//给DamageProperty指针赋值，且构造一个FGameplayEffectAttributeCaptureDefinition对象。
		//解释:主要是获取UAttributeSetBase的Damage
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

	//如果你没有在MMC的构造函数中将FGameplayEffectAttributeCaptureDefinition添加到RelevantAttributesToCapture中
	//并且尝试捕获Attribute, 那么将会得到一个关于捕获时缺失Spec的错误. 如果不需要捕获Attribute, 那么就不必添加什
	//么到RelevantAttributesToCapture.
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	//父类内置:TArray<FGameplayEffectAttributeCaptureDefinition> RelevantAttributesToCapture;
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

