// Copyright © Noé Perard-Gayot 2021.

#include "Game/PTRGameMode.h"
#include "UI/PTRHUD.h"
#include "Characters/PTRCharacter.h"
#include "Player/PTRPlayerState.h"

APTRGameMode::APTRGameMode(const FObjectInitializer& ObjectInitializer)
{
	DefaultPawnClass = APTRCharacter::StaticClass();
	PlayerStateClass = APTRPlayerState::StaticClass();
	HUDClass = APTRHUD::StaticClass();
}