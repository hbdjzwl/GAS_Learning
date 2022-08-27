// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "UObject/Object.h"
#include "GameplayAbility_GrantedBase.generated.h"

/**
 *  Give技能后自动激活。
 */
UCLASS()
class GAS_LEARNING_API UGameplayAbility_GrantedBase : public UGameplayAbility
{
	GENERATED_BODY()

	//当GiveAbility最后会调用该函数
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec);
};
