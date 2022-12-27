// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <AbilitySystemComponent.h>
#include "GAS_BlueprintFunctionLibrary.generated.h"



/**
 * 
 */
UCLASS()
class GAS_LEARNING_API UGAS_BlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/*----------------------- Tag -------------------------*/
	UFUNCTION(BlueprintCallable, Category = "ASC", meta = (DisplayName = "AddLooseGameplayTag"))
	static int32 BPAddLooseGameplayTag(UAbilitySystemComponent* ASC, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "ASC", meta = (DisplayName = "RemoveLooseGameplayTag"))
	static int32 BPRemoveLooseGameplayTag(UAbilitySystemComponent* ASC, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "ASC", meta = (DisplayName = "GetTagCount"))
	static int32 BPGetTagCount(UAbilitySystemComponent* ASC, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "ASC", meta = (DisplayName = "SetTagCount"))
	static int32 BPSetTagCount(UAbilitySystemComponent* ASC, FGameplayTag Tag, int32 NewCount);

	UFUNCTION(BlueprintCallable, Category = "ASC", meta = (DisplayName = "SetReplicationMode"))
	static void BPSetReplicationMode(UAbilitySystemComponent* ASC,EGameplayEffectReplicationMode NewReplicationMode);

	UFUNCTION(BlueprintCallable, Category = "ASC", meta = (DisplayName = "PrintActiveGameplayEffectHandle"))
	static FString BPPrintActiveGameplayEffectHandle (FActiveGameplayEffectHandle Handle, float TimeToDisplay = 2.f);
};
