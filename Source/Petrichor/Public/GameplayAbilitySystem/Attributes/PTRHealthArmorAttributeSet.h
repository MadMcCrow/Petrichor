// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "PTRHealthAttributeSet.h"
#include "PTRHealthArmorAttributeSet.generated.h"

/**
*	Attribute Set for every Object that has armor ( and thus life)
*
*/
UCLASS(ClassGroup=(PTR), minimalapi, Category="PTR|GameplayAbilitySystem")
class UPTRHealthArmorAttributeSet : public UPTRHealthAttributeSet
{
	GENERATED_BODY()

public:
	UPTRHealthArmorAttributeSet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** This measures how much damage can be absorbed before dying. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData Armor;

	/** This measures how much damage can be absorbed before dying. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData MaxArmor;
};