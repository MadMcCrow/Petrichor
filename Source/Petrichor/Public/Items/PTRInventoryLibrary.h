// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "Items/PTRSoftItemPath.h"
#include "PTRInventoryLibrary.generated.h"


/**
 *	Simplifies scripting of interaction by allowing to specify operation as an enum
 *	@note we could have used sign of Count to do so, but I find this less ambiguous
 */
UENUM(BlueprintType, Category="Petrichor|Items")
enum class EPTRItemOperation : uint8
{
	Add		UMETA(DisplayName="Add Item"),
	Remove	UMETA(DisplayName="Remove Item")
};


/**
*	Collection of function to help scripting inventory things
*/
UCLASS( ClassGroup=(PTR), Category="Petrichor|Items")
class PETRICHOR_API UPTRInventoryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 *	Will try to use Inventory Interface to get inventory component
	 *	@return inventory component if succeeded, nullptr otherwise
	 */
	UFUNCTION(BlueprintPure, Category  = "Inventory")
	static class UPTRInventoryComponent* GetInventoryComponent(const AActor* InventoryActor);

	/**
	 *	Will try to use Inventory Interface to get inventory component
	 *	and add or remove Specified Item to the inventory
	 *	@param	InventoryActor	Actor that have an inventory
	 *	@param	Item			The Item to add/Remove
	 *	@param	Count			How much should we change
	 *	@param	Operation		Should we add or remove Items
	 *	@return inventory component if succeeded, nullptr otherwise
	 */
	UFUNCTION(BlueprintCallable, Category  = "Inventory", meta = (Keywords = "Add Remove Item Change Operation"))
	static bool ChangeActorItem(const AActor* InventoryActor, FPTRSoftItemPath Item, int32 Count = 1, EPTRItemOperation Operation = EPTRItemOperation::Add);


	/**
	*	Will try to use Inventory Interface to get inventory component
	*	and add or remove Specified Item to the inventory
	*	@param	InventoryActor	Actor that have an inventory
	*	@param	Item			The Item to add/Remove
	*	@param	Count			How much should we change
	*	@param	Operation		Should we add or remove Items
	*	@return inventory component if succeeded, nullptr otherwise
	*/
	UFUNCTION(BlueprintCallable, Category  = "Inventory", meta = (Keywords = "Add Remove Item Change Operation Asset"))
	static bool ChangeActorItemAsset(const AActor* InventoryActor,UPARAM(meta=(AllowedClasses="PTRItem")) TSoftObjectPtr<UPTRItem> Item, int32 Count = 1, EPTRItemOperation Operation = EPTRItemOperation::Add);


};
