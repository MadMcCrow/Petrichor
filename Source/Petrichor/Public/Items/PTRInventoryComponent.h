// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"

#include "Items/PTRSoftItemPath.h"
#include "PTRInventoryComponent.generated.h"

// forward declaration
class UPTRItem;
class UPTRInventoryComponent;

// log for inventory
DECLARE_LOG_CATEGORY_EXTERN(LogPTRInventory, Log, All);


/**
 *	Advanced struct for holding items counts
 *	@todo : Add custom serialisation (Net), equality , etc ...
 */
USTRUCT(BlueprintType, Category="Petrichor|Items")
struct FPTRInventoryItem : public FTableRowBase
{
	GENERATED_BODY()

public:

	/**
	 *	Unique ID of that Item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowedClasses="PTRItem"))
	FPrimaryAssetId AssetId;

	/**
	 *	Amount stored
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count;

	/**
	 *	Parametric CTR
	 *	will make sure there's a valid item with that path
	 */
	FPTRInventoryItem(const FPTRSoftItemPath& Path, int32 Num = 0);

	/**
	*	Parametric CTR with Templated param
	*/
	FPTRInventoryItem(const TSoftObjectPtr<UPTRItem>& Path, int32 Num = 0);

	// default CTR
	FPTRInventoryItem(): AssetId(FPrimaryAssetId()), Count(0)
	{
	}

	// hash for Set and maps
	FORCEINLINE friend uint32 GetTypeHash(const FPTRInventoryItem& Key)
	{
		// basically call super
		return GetTypeHash(Key.AssetId);
	}

	// equal operator for comparisons
	bool operator==(const FPTRInventoryItem& Other) const
	{
		const uint32 A = GetTypeHash(*this);
		const uint32 B = GetTypeHash(Other);
		return A == B;
	}

	// implicit conversion operator
	operator FPrimaryAssetId() const {return AssetId;}

	operator FPTRSoftItemPath() const {return FPTRSoftItemPath(AssetId);}

	// To string export function
	FString ToString() const {return AssetId.ToString();}

	FSoftObjectPath ToSoftPath() const;

	int32 GetCount() const {return Count;}

	bool IsNull() const;


	/** Serializer to simplify it's serialisation */
	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

// register the Net Serializer for the Inventory Item to improve performance
template<>
struct TStructOpsTypeTraits<FPTRInventoryItem> : public TStructOpsTypeTraitsBase2<FPTRInventoryItem>
{
	enum { WithNetSerializer	= true,	};
};

/**
 *	Multicast event type for when an inventory item changes
 *	This is not network related and will in fact be broadcast only on machines calling the broadcast function
 */
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FOnInventoryItemChange, UPTRInventoryComponent, OnUpdateItem, const FPTRInventoryItem &, InventoryItemChanged);

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
	bool AddItem(const FPTRSoftItemPath& Item, int32 Count);

	/**
	 *  RemoveItem
	 *  @brief  remove Item from inventory
	 *  @return true if succeeded, false otherwise
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool RemoveItem( const FPTRSoftItemPath& Item, int32 Count);

	/**
	 *  ItemCount
	 *  @brief  the amount of an item we store
	 *  @return The amount of the item stored, or 0 if not present
	 */
	UFUNCTION(BlueprintPure, Category="Inventory")
	int32 ItemCount(const FPTRSoftItemPath& Item) const;

	/**
	 *  ItemCount
	 *  @brief  do we store a certain item
	 *  @return The amount of the item stored, or 0 if not present
	 */
	UFUNCTION(BlueprintPure, Category="Inventory")
	bool HasItem(const FPTRSoftItemPath& Item) const;

	/**
	*  GetItems
	*  @brief  Getter for the item set.
	*  meant for debugging
	*/
	UFUNCTION(BlueprintPure, Category="Inventory")
	TSet<FPTRInventoryItem> GetItems() const;


	/**
	 * Init the inventory with a predetermined set
	 * @note can only be called from server
	 */
	UFUNCTION()
	void InitInventory(TSet<FPTRInventoryItem> &InitItems);


protected:
	/**
	 *  try to add Item on the server side
	 *  Server will check the item and then try to add it to the inventory
	 *  Will call @see Net_OnAddItem on successful completion
	 */
	UFUNCTION(Server, Reliable, WithValidation)
	void Net_UpdateItem(const FPTRInventoryItem& Item);
	virtual void Net_UpdateItem_Implementation(const FPTRInventoryItem& Item);
	virtual bool Net_UpdateItem_Validate(const FPTRInventoryItem& Item) const;


	/**
	 *  Update the Inventory on all clients with the new value server found
	 *  if a key is already present, we override that key
	 *  if count is 0, we remove the key.
	 */
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Net_OnUpdateItem(const FPTRInventoryItem& Item);
	virtual void Net_OnUpdateItem_Implementation(const FPTRInventoryItem& Item);
	virtual bool Net_OnUpdateItem_Validate(const FPTRInventoryItem& Item) const;


public:

	/**
	 *	Simple event called on all machines when inventory items are updated
	 *
	 *	This is meant for other components to
	 */
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnInventoryItemChange OnUpdateItem;

private:

	/**
	 *  The items this inventory has
	 *  FPTRInventoryItem provide a hash function to ensure that there's no double
	 *  TSet ensure faster searches compared to arrays.
	 */
	UPROPERTY(Transient, VisibleAnywhere, Category="Inventory")
	TSet<FPTRInventoryItem> Items;


};
