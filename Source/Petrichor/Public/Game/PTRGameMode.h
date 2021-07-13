// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "PTRGameMode.generated.h"

UCLASS(ClassGroup=(PTR), minimalapi)
class APTRGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APTRGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};