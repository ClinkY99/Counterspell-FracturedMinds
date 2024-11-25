// Copyright Epic Games, Inc. All Rights Reserved.

#include "bHorrerJamGameMode.h"
#include "bHorrerJamCharacter.h"
#include "UObject/ConstructorHelpers.h"

AbHorrerJamGameMode::AbHorrerJamGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
