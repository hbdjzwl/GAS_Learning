// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS_AttributeSet.h"

#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UGAS_AttributeSet::UGAS_AttributeSet()
{
}

bool UGAS_AttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
	UE_LOG(LogTemp,Warning,TEXT("AH::PreGameplayEffectExecute ----- %s"),*UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetOwningActor()->GetLocalRole()));
}

void UGAS_AttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	UE_LOG(LogTemp,Warning,TEXT("AH::PreAttributeChange ----- %s"),*UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetOwningActor()->GetLocalRole()));
}

void UGAS_AttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	UE_LOG(LogTemp,Warning,TEXT("AH::PreAttributeBaseChange ----- %s"),*UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetOwningActor()->GetLocalRole()));

}

void UGAS_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	UE_LOG(LogTemp,Warning,TEXT("AH::PostGameplayEffectExecute ----- %s"),*UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetOwningActor()->GetLocalRole()));
	
}

void UGAS_AttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, Health, OldHealth);
}

void UGAS_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, MaxHealth, OldMaxHealth);
}

void UGAS_AttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, Mana, OldMana);
}

void UGAS_AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, MaxMana, OldMaxMana);
}

void UGAS_AttributeSet::OnRep_PhysicalDamage(const FGameplayAttributeData& OldPhysicalDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, PhysicalDamage, OldPhysicalDamage);
}

void UGAS_AttributeSet::OnRep_PhysicalDamageCoefficient(const FGameplayAttributeData& OldPhysicalDamageCoefficient)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, PhysicalDamageCoefficient, OldPhysicalDamageCoefficient);
}



void UGAS_AttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, Armor, OldArmor);
}

void UGAS_AttributeSet::OnRep_Speed(const FGameplayAttributeData& OldSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, Speed, OldSpeed);
}

void UGAS_AttributeSet::OnRep_Damage(const FGameplayAttributeData& OldDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, Damage, OldDamage);
}

void UGAS_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, Health,	COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, MaxHealth,COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, Health,	COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, MaxHealth,COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, Armor,	COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, Speed,	COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, PhysicalDamage,	COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, PhysicalDamageCoefficient,	COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, Damage,	COND_None, REPNOTIFY_Always)
	
}
