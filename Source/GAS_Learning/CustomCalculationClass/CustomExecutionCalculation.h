// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "CustomExecutionCalculation.generated.h"

/**
 * 
 */
UCLASS()
class GAS_LEARNING_API UCustomExecutionCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UCustomExecutionCalculation();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
