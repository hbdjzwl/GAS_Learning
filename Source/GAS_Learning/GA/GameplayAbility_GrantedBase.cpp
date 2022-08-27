// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_GrantedBase.h"
#include "AbilitySystemComponent.h"

void UGameplayAbility_GrantedBase::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo,
                                               const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);
	
	ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
}
