// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "Items/PTRPickupItem.h"
#include "PTRAttribute.generated.h"

/**
 *	Attribute class : Life, Stamina, etc...
 */
UCLASS(Abstract, NotBlueprintable, ClassGroup=(PTR), Category="Petrichor|Items", HideCategories=("Item|Display", "Item|System"))
class PETRICHOR_API UPTRAttribute : public UPTRPickupItem
{
	GENERATED_BODY()

public:
	// Default CTR
	UPTRAttribute(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	/**
	*  The unique name for this item
	*/
	UPROPERTY(VisibleAnywhere, blueprintReadOnly, Category="Item|Attribute")
	FName AttributeName;


};