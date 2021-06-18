// Copyright Epic Games, Inc. All Rights Reserved.

#include "Game/PTRGameMode.h"
#include "UI/PTRHUD.h"
#include "Characters/PTRCharacter.h"
#include "UObject/ConstructorHelpers.h"

APTRGameMode::APTRGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = APTRCharacter::StaticClass();

	// use our custom HUD class
	HUDClass = APTRHUD::StaticClass();
}
