// Copyright Epic Games, Inc. All Rights Reserved.

#include "PTRGameMode.h"
#include "PTRHUD.h"
#include "PTRCharacter.h"
#include "UObject/ConstructorHelpers.h"

APTRGameMode::APTRGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = APTRHUD::StaticClass();
}
