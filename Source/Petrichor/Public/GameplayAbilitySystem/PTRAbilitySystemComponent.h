// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "AbilitySystemComponent.h"
#include "PTRAbilitySystemComponent.generated.h"

/**
 *	Ability System Component for PTR
 *	if any special behaviour needs to be implemented it can be done here.
 */
UCLASS(ClassGroup=(PTR), minimalapi, Category="PTR|GameplayAbilitySystem", HideCategories=("Sockets","Collision"))
class UPTRAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	// CTR
	UPTRAbilitySystemComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// UAbilitySystemComponent API
	virtual void BeginPlay() override;
	virtual bool ShouldDoServerAbilityRPCBatch() const override { return true; }	// Turn on RPC batching in ASC. Off by default.
	// \UAbilitySystemComponent API


protected:

	/**
	 *	A list of effects to apply at start-up
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AbilitySystem")
	TSet<TSoftClassPtr<UGameplayEffect>> DefaultEffects;

};