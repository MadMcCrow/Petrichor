// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "PTRAttributeInterface.generated.h"

// forward declaration
class UPTRInventoryComponent;

/**
 *	Simple Interface to easily add attributes to a Character or PlayerState
 */
UINTERFACE(MinimalAPI, Blueprintable, Category="Petrichor|Attributes")
class UPTRAttributeInterface : public UInterface
{
	GENERATED_BODY()
};

class IPTRAttributeInterface
{
	GENERATED_BODY()

public:
	/** return Inventory component */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category  = "Attributes")
	UPTRInventoryComponent* GetInventoryComponent() const;
	virtual UPTRInventoryComponent* GetInventoryComponent_Implementation() const PURE_VIRTUAL(,return nullptr;)
};