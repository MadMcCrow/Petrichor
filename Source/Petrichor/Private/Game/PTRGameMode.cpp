// Copyright © Noé Perard-Gayot 2021.

#include "Game/PTRGameMode.h"
#include "UI/PTRHUD.h"
#include "Characters/PTRCharacter.h"

APTRGameMode::APTRGameMode() : Super()
{

	DefaultPawnClass = APTRCharacter::StaticClass();
	HUDClass = APTRHUD::StaticClass();
}