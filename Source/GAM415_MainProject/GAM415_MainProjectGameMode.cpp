// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAM415_MainProjectGameMode.h"
#include "GAM415_MainProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGAM415_MainProjectGameMode::AGAM415_MainProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
