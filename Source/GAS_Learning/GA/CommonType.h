// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CommonType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class GA_InputID :uint8
{
    None,
	Confirm,
	Cancel,
	Jump,
	Sprint,
};


USTRUCT(BlueprintType)
struct FBindInputID: public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	GA_InputID InputID;
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	TSubclassOf<class UGameplayAbility> SkillClass;
};
