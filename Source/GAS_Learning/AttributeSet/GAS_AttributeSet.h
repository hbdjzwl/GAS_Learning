#include "GameplayEffectExtension.h"// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GAS_AttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class GAS_LEARNING_API UGAS_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:

	UGAS_AttributeSet();

	//目前已知也是修改Base值调用
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData &Data) override;

	//用于Current值修改前调用
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	//对于Base值修改前的调用
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	
	//对于Base值的修改后调用
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;
	
	
	// 血量 && 最大血量
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Abilities", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, Health);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Abilities", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, MaxHealth);

	// 魔法 && 魔法值
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Abilities", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, Mana);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Abilities", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, MaxMana);

	// 攻击力
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Abilities", ReplicatedUsing = OnRep_PhysicalDamage)
	FGameplayAttributeData PhysicalDamage ;
	ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, PhysicalDamage);
	
	// 攻击力系数
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Abilities", ReplicatedUsing = OnRep_PhysicalDamageCoefficient)
	FGameplayAttributeData PhysicalDamageCoefficient ;
	ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, PhysicalDamageCoefficient);
	
	// 护甲
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Abilities", ReplicatedUsing = OnRep_Armor)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, Armor);

	// 速度
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Abilities", ReplicatedUsing = OnRep_Speed)
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, Speed);


	/* ------------------------------------------- */
	// 临时伤害值:用于传输伤害值。GE_Instant 即可修改的Base值值
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Abilities", ReplicatedUsing = OnRep_Damage)
	FGameplayAttributeData Damage ;
	ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, Damage);
	
	
	UFUNCTION()
    virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	UFUNCTION()
    virtual void OnRep_Mana(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldMaxHealth);
	UFUNCTION()
	virtual void OnRep_PhysicalDamage(const FGameplayAttributeData& OldPhysicalDamage);
	UFUNCTION()
	virtual void OnRep_PhysicalDamageCoefficient(const FGameplayAttributeData& OldPhysicalDamageCoefficient);
	UFUNCTION()
	virtual void OnRep_Armor(const FGameplayAttributeData& OldMaxHealth);
	UFUNCTION()
	virtual void OnRep_Speed(const FGameplayAttributeData& OldSpeed);


	UFUNCTION()
	virtual void OnRep_Damage(const FGameplayAttributeData& OldDamage);
};
