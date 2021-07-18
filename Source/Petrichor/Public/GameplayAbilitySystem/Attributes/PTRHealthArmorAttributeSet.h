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

	/** This measures how much damage can be absorbed before loosing health. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Attributes|Armor", ReplicatedUsing = OnRep_Armor)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UPTRHealthArmorAttributeSet, Armor)

	/**
	* This defines how much armor you can have.
	* @note : we might use a different system for this: Pickup could define how much they had based on what's already there
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Attributes|Armor", ReplicatedUsing = OnRep_MaxArmor)
	FGameplayAttributeData MaxArmor;
	ATTRIBUTE_ACCESSORS(UPTRHealthArmorAttributeSet, MaxArmor)

protected:

	UFUNCTION()
	virtual void OnRep_Armor(const FGameplayAttributeData& OldArmor);
	UFUNCTION()
	virtual void OnRep_MaxArmor(const FGameplayAttributeData& OldMaxArmor);
};