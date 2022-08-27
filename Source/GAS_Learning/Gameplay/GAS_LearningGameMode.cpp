// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAS_LearningGameMode.h"
#include "GAS_LearningCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGAS_LearningGameMode::AGAS_LearningGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
