// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "PTRHealthArmorAttributeSet.h"
#include "PTRCharacterAttributeSet.generated.h"

/**
*	Attribute Set for every Object that has armor ( and thus life)
*
*/
UCLASS(ClassGroup=(PTR), minimalapi, Category="PTR|GameplayAbilitySystem")
class UPTRCharacterAttributeSet : public UPTRHealthArmorAttributeSet
{
	GENERATED_BODY()

public:
	UPTRCharacterAttributeSet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};