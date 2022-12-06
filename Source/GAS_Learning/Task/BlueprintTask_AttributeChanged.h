// Copyright 2020 Dan Kestranek.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AbilitySystemComponent.h"
#include "BlueprintTask_AttributeChanged.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCustomAttributeChanged, FGameplayAttribute, Attribute, float, NewValue, float, OldValue);

/**
 * Blueprint node to automatically register a listener for all attribute changes in an AbilitySystemComponent.
 * Useful to use in UI.
 */
UCLASS(BlueprintType, meta = (ExposedAsyncProxy = AsyncTask))
class GAS_LEARNING_API UBlueprintTask_AttributeChanged : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnCustomAttributeChanged OnAttributeChanged;

	//监听单个属性的修改
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UBlueprintTask_AttributeChanged* ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute);

	//监听多个属性的修改
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UBlueprintTask_AttributeChanged* ListenForAttributesChange(UAbilitySystemComponent* AbilitySystemComponent, TArray<FGameplayAttribute> Attributes);

	// 取消Task时，需手动调用
	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:
	UPROPERTY()
	UAbilitySystemComponent* ASC;

	FGameplayAttribute AttributeToListenFor;
	TArray<FGameplayAttribute> AttributesToListenFor;

	void AttributeChanged(const FOnAttributeChangeData& Data);
};
