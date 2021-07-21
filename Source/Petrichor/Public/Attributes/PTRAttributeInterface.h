// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "PTRAttributeInterface.generated.h"

/**
 *	Simple interface to make attribute component work with inventory component
 *	This interface can be added in C++ and in BP
 *	it helps the attribute component to interact with the inventory component
 */
UINTERFACE(MinimalAPI, Blueprintable, Category="PTR|Attribute")
class UPTRAttributeInterface : public UInterface
{
	GENERATED_BODY()
};

class IPTRAttributeInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PTR|Attribute|Interface")
	class UPTRInventoryComponent* GetInventoryComponent() const;
	virtual class UPTRInventoryComponent* GetInventoryComponent_Implementation() const;

};