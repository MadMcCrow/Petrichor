// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "PTRInventoryInterface.generated.h"

// forward declaration
class UPTRInventoryComponent;

/**
 *	Simple Interface to easily get inventory on a class
 */
UINTERFACE(MinimalAPI, Blueprintable, Category="Petrichor|Attributes")
class UPTRInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

class IPTRInventoryInterface
{
	GENERATED_BODY()

public:
	/** return Inventory component */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category  = "Attributes")
	UPTRInventoryComponent* GetInventoryComponent() const;
	virtual UPTRInventoryComponent* GetInventoryComponent_Implementation() const PURE_VIRTUAL(,return nullptr;)
};
