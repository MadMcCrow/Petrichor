// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "PTRCharacterBase.h"
#include "PTRCharacter.generated.h"


UCLASS(Abstract, Blueprintable, config=Game)
class APTRCharacter : public APTRCharacterBase
{
	GENERATED_BODY()
public:

	APTRCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};