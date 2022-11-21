// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "CustomCalculationModify.generated.h"

/**
 * 
 */
UCLASS()
class GAS_LEARNING_API UCustomCalculationModify : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UCustomCalculationModify();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	
};
