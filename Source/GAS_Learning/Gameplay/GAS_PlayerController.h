// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GAS_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAS_LEARNING_API AGAS_PlayerController : public APlayerController
{
	GENERATED_BODY()

	//客户端被控制时调用
	virtual void AcknowledgePossession(class APawn* P);
};
