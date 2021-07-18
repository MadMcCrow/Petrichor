// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PTRHealthAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#ifndef ATTRIBUTE_ACCESSORS
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
#endif

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

	/**
	 * This basically measures how much damage can be absorbed before dying.
	 */
	UPROPERTY(BlueprintReadOnly, Category ="Attributes|Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UPTRHealthAttributeSet, Health)

	/**
	 * This defines how much health you can have.
	 * @note : we might use a different system for this: Pickup could define how much they had based on what's already there
	 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Attributes|Health", ReplicatedUsing = OnRep_MaxHealth)
    FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UPTRHealthAttributeSet, MaxHealth)

private:

	/**
	* These OnRep functions exist to make sure that the ability system internal representations are synchronized properly during replication
	**/

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

};