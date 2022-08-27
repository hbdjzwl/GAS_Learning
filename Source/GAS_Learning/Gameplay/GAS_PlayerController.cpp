// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS_PlayerController.h"
#include "GAS_LearningCharacter.h"
void AGAS_PlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);
	if(	AGAS_LearningCharacter* MyPawn= Cast<AGAS_LearningCharacter>(P))
	{
		MyPawn->GetAbilitySystemComponent()->InitAbilityActorInfo(MyPawn, MyPawn); //客户端初始化GAS
		MyPawn->Sever_InitializPassiveSkill(); //激活被动技能
		MyPawn->Sever_InitializBindInputAbility();//绑定输入的
	}
}
