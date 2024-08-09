// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <AbilitySystemComponent.h>
#include "../../../../../../UnrealEngine/UnrealEngine-4.27-plus/Engine/Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/GameplayAbility.h"
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
	UFUNCTION(BlueprintCallable, Category = "Ability", meta = (DisplayName = "AddLooseGameplayTag"))
	static int32 BPAddLooseGameplayTag(UAbilitySystemComponent* ASC, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "Ability", meta = (DisplayName = "RemoveLooseGameplayTag"))
	static int32 BPRemoveLooseGameplayTag(UAbilitySystemComponent* ASC, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "Ability", meta = (DisplayName = "GetTagCount"))
	static int32 BPGetTagCount(UAbilitySystemComponent* ASC, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "Ability", meta = (DisplayName = "SetTagCount"))
	static int32 BPSetTagCount(UAbilitySystemComponent* ASC, FGameplayTag Tag, int32 NewCount);

	UFUNCTION(BlueprintCallable, Category = "Ability", meta = (DisplayName = "SetReplicationMode"))
	static void BPSetReplicationMode(UAbilitySystemComponent* ASC,EGameplayEffectReplicationMode NewReplicationMode);



	/*----------------------- GA -------------------------*/

	UFUNCTION(BlueprintCallable, Category = "Ability", meta = (DisplayName = "PrintActiveGameplayEffectHandle"))
	static FString BPPrintActiveGameplayEffectHandle (FActiveGameplayEffectHandle Handle, float TimeToDisplay = 2.f);

	UFUNCTION(BlueprintPure, Category = "Ability", meta = (DisplayName = "GetCurrentPredictionKeyStatus"))
	static FString GetCurrentPredictionKeyStatus(UAbilitySystemComponent* AbilitySystemComponent);


	UFUNCTION(BlueprintPure, Category = "Ability")
	static FGameplayAbilitySpecHandle FindAbilitySpecHanleFromClass(UAbilitySystemComponent* AbilitySystemComponent,TSubclassOf<UGameplayAbility> InAbilityClass);

	UFUNCTION(BlueprintPure, Category = "Ability")
	static FGameplayAbilitySpecHandle FindAbilitySpecHandleFromInputID(UAbilitySystemComponent* AbilitySystemComponent, int32 InputID);


	UFUNCTION(BlueprintCallable, Category = "Ability")
	static UGameplayAbility* GetPrimaryAbilityInstanceFromHandle(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAbilitySpecHandle Handle);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	static UGameplayAbility* GetPrimaryAbilityInstanceFromClass(UAbilitySystemComponent* AbilitySystemComponent, TSubclassOf<UGameplayAbility> InAbilityClass);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	static FGameplayAbilitySpecHandle GetCurrentAbilitySpecHandle(UGameplayAbility* GameplayAbility);

	UFUNCTION(BlueprintPure, Category = "Ability")
	static FString AbilitySpecHandleToString(FGameplayAbilitySpecHandle GameplayAbilitySpecHandle);
};
