// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "AbilitySystemComponent.h"
#include "PTRAbilitySystemComponent.generated.h"

/**
 *	Ability System Component for PTR
 *	if any special behaviour needs to be implemented it can be done here.
 */
UCLASS(ClassGroup=(PTR), minimalapi, Category="PTR|GameplayAbilitySystem")
class UPTRAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	// CTR
	UPTRAbilitySystemComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get())
	: Super(ObjectInitializer)
	{

	}

};