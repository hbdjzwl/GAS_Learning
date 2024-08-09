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

FString UGAS_BlueprintFunctionLibrary::GetCurrentPredictionKeyStatus(UAbilitySystemComponent* AbilitySystemComponent)
{
	return AbilitySystemComponent->ScopedPredictionKey.ToString() + " is valid for more prediction: " + (AbilitySystemComponent->ScopedPredictionKey.IsValidForMorePrediction() ? TEXT("true") : TEXT("false"));
}

FGameplayAbilitySpecHandle UGAS_BlueprintFunctionLibrary::FindAbilitySpecHanleFromClass(UAbilitySystemComponent* AbilitySystemComponent, TSubclassOf<UGameplayAbility> InAbilityClass)
{
	if (AbilitySystemComponent)
	{
		if (FGameplayAbilitySpec* Spec = AbilitySystemComponent->FindAbilitySpecFromClass(InAbilityClass))
		{
			return Spec->Handle;
		}

	}
	return FGameplayAbilitySpecHandle();
}


FGameplayAbilitySpecHandle UGAS_BlueprintFunctionLibrary::FindAbilitySpecHandleFromInputID(UAbilitySystemComponent* AbilitySystemComponent, int32 InputID)
{
	if (AbilitySystemComponent)
	{
		if (FGameplayAbilitySpec* Spec = AbilitySystemComponent->FindAbilitySpecFromInputID(InputID))
		{
			return Spec->Handle;
		}
	}
	return FGameplayAbilitySpecHandle();

}

UGameplayAbility* UGAS_BlueprintFunctionLibrary::GetPrimaryAbilityInstanceFromHandle(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAbilitySpecHandle Handle)
{
	if (AbilitySystemComponent)
	{
		if (FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromHandle(Handle))
		{
			return AbilitySpec->GetPrimaryInstance();
		}
	}
	return nullptr;
}

UGameplayAbility* UGAS_BlueprintFunctionLibrary::GetPrimaryAbilityInstanceFromClass(UAbilitySystemComponent* AbilitySystemComponent, TSubclassOf<UGameplayAbility> InAbilityClass)
{
	if (AbilitySystemComponent)
	{
		if (FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromClass(InAbilityClass))
		{
			return AbilitySpec->GetPrimaryInstance();
		}
	}
	return nullptr;
}

FGameplayAbilitySpecHandle UGAS_BlueprintFunctionLibrary::GetCurrentAbilitySpecHandle(UGameplayAbility* GameplayAbility)
{
	if (GameplayAbility)
	{
		return GameplayAbility->GetCurrentAbilitySpecHandle();
	}
	return FGameplayAbilitySpecHandle();
}

FString UGAS_BlueprintFunctionLibrary::GetCurrentAbilitySpecHandle(FGameplayAbilitySpecHandle GameplayAbilitySpecHandle)
{
	return GameplayAbilitySpecHandle.ToString();
}

