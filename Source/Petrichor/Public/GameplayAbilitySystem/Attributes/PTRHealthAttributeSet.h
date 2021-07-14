// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "AttributeSet.h"
#include "PTRHealthAttributeSet.generated.h"

/**
 *	Attribute Set for every Object that has life.
 *
 */
UCLASS(ClassGroup=(PTR), minimalapi, Category="PTR|GameplayAbilitySystem")
class UPTRHealthAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPTRHealthAttributeSet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


	/** This measures how much damage can be absorbed before dying. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    FGameplayAttributeData Health;

	/** This measures how much damage can be absorbed before dying. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    FGameplayAttributeData MaxHealth;
};