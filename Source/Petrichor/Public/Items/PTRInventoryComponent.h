// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PTRInventoryComponent.generated.h"

// forward declaration
class UPTRItem;


DECLARE_LOG_CATEGORY_EXTERN(LogPTRInventory, Log, All);

/**
 *	Advanced struct for holding items counts
 */
USTRUCT(BlueprintType, Category="Petrichor|Items")
struct FPTRInventoryItem : public FPrimaryAssetId
{
	GENERATED_BODY()

public:

	/** Amount stored */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count;

	/**
	 *	Parametric CTR
	 *	will make sure there's a valid item with that path
	 */
	FPTRInventoryItem(const FSoftObjectPath& Path, int32 Num = 0);

	/**
	*	Parametric CTR with Templated param
	*/
	FPTRInventoryItem(const TSoftObjectPtr<UPTRItem>& Path, int32 Num = 0) : FPTRInventoryItem(Path.ToSoftObjectPath(), Num)
	{
	}

	// default CTR
	FPTRInventoryItem(): FPrimaryAssetId(), Count(0)
	{
	}

	// hash for Set and maps
	inline friend uint32 GetTypeHash(const FPTRInventoryItem& Key)
	{
		// basically call super
		return GetTypeHash(FPrimaryAssetId(Key));
	}

	// equal operator for comparisons
	inline bool operator==(const FPTRInventoryItem& Other) const
	{
		const uint32 A = GetTypeHash(*this);
		const uint32 B = GetTypeHash(Other);
		// ignore negative counts
		if (this->Count < 0 || Other.Count < 0)
		{
			return A == B;
		}
		return A == B && Count == Other.Count;
	}

	bool IsNull() const;
};

/**
 *  UPTRInventoryComponent
 *  @brief handles Players Inventory
 *  @note  this could be used for other actors that stores multiple items and needs a way to add and remove those items
 */
UCLASS(ClassGroup=(PTR), config=Game, Category="Petrichor|Items")
class UPTRInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Default CTR
	UPTRInventoryComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**
	 *  AddItem
	 *  @brief  Add Item to inventory
	 *  @return true if succeeded, false otherwise
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool AddItem(const TSoftObjectPtr<UPTRItem>& Item, int32 Count);

	/**
	 *  RemoveItem
	 *  @brief  remove Item from inventory
	 *  @return true if succeeded, false otherwise
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool RemoveItem(const TSoftObjectPtr<UPTRItem>& Item, int32 Count);

	/**
	 *  ItemCount
	 *  @brief  the amount of an item we store
	 *  @return The amount of the item stored, or 0 if not present
	 */
	UFUNCTION(BlueprintPure, Category="Inventory")
	int32 ItemCount(const TSoftObjectPtr<UPTRItem>& Item) const;

	/**
	 *  ItemCount
	 *  @brief  do we store a certain item
	 *  @return The amount of the item stored, or 0 if not present
	 */
	UFUNCTION(BlueprintPure, Category="Inventory")
	bool HasItem(const TSoftObjectPtr<UPTRItem>& Item) const;

	/**
	 * Simple getter that returns the path without loading the object.
	 */
	UFUNCTION(BlueprintPure, Category="ItemID")
	static TSoftObjectPtr<UPTRItem> GetAssetFromID(const FPrimaryAssetId& AssetID);

	/**
	* Simple getter that loads synchronously an item and gets it's correct info.
	* @note Making this async would complexify much without real benefits
	* (we would have to make all our server calls two passes)
	*/
	UFUNCTION(BlueprintPure, Category="ItemID")
	static FPrimaryAssetId GetAssetID( const TSoftObjectPtr<UPTRItem>& Item);


protected:
	/**
	 *  try to add Item on the server side
	 *  Server will check the item and then try to add it to the inventory
	 *  Will call @see Net_OnAddItem on successful completion
	 */
	UFUNCTION(Server, Reliable, WithValidation)
	void Net_UpdateItem(const FPTRInventoryItem& Item);
	void Net_UpdateItem_Implementation(const FPTRInventoryItem& Item);
	bool Net_UpdateItem_Validate(const FPTRInventoryItem& Item) const;


	/**
	 *  Update the Inventory on all clients with the new value server found
	 *  if a key is already present, we override that key
	 *  if count is 0, we remove the key.
	 */
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Net_OnUpdateItem(const FPTRInventoryItem& Item);
	void Net_OnUpdateItem_Implementation(const FPTRInventoryItem& Item);
	bool Net_OnUpdateItem_Validate(const FPTRInventoryItem& Item) const;

private:
	/**
	 *  The items this inventory has
	 *  FPTRInventoryItem provide a hash function to ensure that there's no double
	 *  TSet ensure faster searches compared to arrays.
	 */
	UPROPERTY(Transient, VisibleAnywhere, Category="Inventory")
	TSet<FPTRInventoryItem> Items;


};