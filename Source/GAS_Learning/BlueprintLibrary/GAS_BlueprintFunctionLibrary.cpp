// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS_BlueprintFunctionLibrary.h"
//#include "Engine/Engine.h"

int32 UGAS_BlueprintFunctionLibrary::BPAddLooseGameplayTag(UAbilitySystemComponent* ASC, FGameplayTag Tag)
{
	ASC->AddLooseGameplayTag(Tag);
	return ASC->GetTagCount(Tag);
}

int32 UGAS_BlueprintFunctionLibrary::BPRemoveLooseGameplayTag(UAbilitySystemComponent* ASC, FGameplayTag Tag)
{
	ASC->RemoveLooseGameplayTag(Tag);
	return ASC->GetTagCount(Tag);
}

int32 UGAS_BlueprintFunctionLibrary::BPGetTagCount(UAbilitySystemComponent* ASC, FGameplayTag Tag)
{
	return ASC->GetTagCount(Tag);
}

int32 UGAS_BlueprintFunctionLibrary::BPSetTagCount(UAbilitySystemComponent* ASC, FGameplayTag Tag, int32 NewCount)
{
	ASC->SetLooseGameplayTagCount(Tag, NewCount);
	return ASC->GetTagCount(Tag);
}

void UGAS_BlueprintFunctionLibrary::BPSetReplicationMode(UAbilitySystemComponent* ASC, EGameplayEffectReplicationMode NewReplicationMode)
{
	ASC->SetReplicationMode(NewReplicationMode);
}

FString UGAS_BlueprintFunctionLibrary::BPPrintActiveGameplayEffectHandle(FActiveGameplayEffectHandle Handle, float TimeToDisplay)
{
	//GEngine->AddOnScreenDebugMessage(-1,TimeToDisplay,FColor::Green, Handle.ToString());
	return Handle.ToString();
}

