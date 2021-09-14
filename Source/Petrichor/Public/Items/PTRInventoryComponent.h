// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Items/PTRSoftItemPath.h"
#include "PTRInventoryComponent.generated.h"

// forward declaration
class UPTRItem;
class UPTRInventoryComponent;

// log for inventory
DECLARE_LOG_CATEGORY_EXTERN(LogPTRInventory, Log, All);


/**
 *	Multicast event type for when an inventory item changes
 *	This is not network related and will in fact be broadcast only on machines calling the broadcast function
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemChange, const FPTRSoftItemPath &, Item, int32, Count);

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
	 *  @brief	Add Item to inventory
	 *  @note	Should be called from server to really happen
	 *  @return	true if succeeded, false otherwise
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool AddItem(const FPTRSoftItemPath& Item, int32 Count);

	/**
	 *  RemoveItem
	 *  @brief	remove Item to inventory
	 *  @note	Should be called from server to really happen
	 *  @return	true if succeeded, false otherwise
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
	*  @param bSynchronisedOnly	 if true, Only return the items has validated by server
	*/
	UFUNCTION(BlueprintPure, Category="Inventory")
	TMap<FPTRSoftItemPath, int32> GetItems(bool bSynchronisedOnly = false) const;


	/**
	 * Init the inventory with a predetermined set
	 * @note can only be called from server
	 */
	UFUNCTION(BlueprintCallable)
	void InitInventory(const TMap<FPTRSoftItemPath, int32> &InitItems);

	/**
	 *	OnLocalUpdateItem Event
	 *	Item has been updated locally
	 */
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnInventoryItemChange OnLocalUpdateItem;

	/**
	 *	OnItemSync Event
	 *	Item has been updated from server
	 */
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnInventoryItemChange OnItemSync;

protected:

	/**
	*	MaxLocalDelta
	*	How many delta can we have before updating
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Network")
	bool bUseMaxDelta;

	/**
	*	MaxLocalDelta
	*	How many delta can we have before updating
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Network", meta = (EditCondition = "bUseMaxDelta"))
	int32 MaxLocalDelta;


	/**
	 *	UpdateItem
	 *	@brief Updates inventory
	 *	@param ItemKey		The new value for this item
	 *	@param bForceSync	Wether we need to request synchronisation with server
	 */
	UFUNCTION()
	void UpdateItem(const FPTRSoftItemPath& Item, int32 Count, bool bForceSync = false);

	/**
	 *	Net_SyncInventory
	 *	Server will apply it's change to clients
	 */
	UFUNCTION(Server, Reliable, WithValidation)
	void Net_RequestSyncInventory();
	virtual void Net_RequestSyncInventory_Implementation();
	virtual bool Net_RequestSyncInventory_Validate() const {return true;}

	/**
	 *	Net_SyncInventory
	 *	Server will apply it's change to clients
	 *	@param Changes	The changes to apply to @see Items
	 */
	UFUNCTION(Client, Reliable, WithValidation)
	void Net_SyncInventory(const TMap<FPTRSoftItemPath, int32> &Changes);
	virtual void Net_SyncInventory_Implementation(const TMap<FPTRSoftItemPath, int32> &Changes);
	virtual bool Net_SyncInventory_Validate(const TMap<FPTRSoftItemPath, int32> &Changes) const {return true;}



private:

	/**
	 *	Items
	 *	@brief The confirmed inventory of the Component
	 *
	 *	 This inventory correspond to the one synced by Server
	 *
	 *  @note	Using TMap for simplicity
	 */
	UPROPERTY(Transient, VisibleAnywhere, Category="Inventory")
	TMap<FPTRSoftItemPath, int32> Items;

	/**
	 *	LocalDeltaItems
	 *	@note all deltas to the Items
	 *	@brief The locally changes in Items
	 */
	UPROPERTY(Transient, VisibleAnywhere, Category="Inventory")
	TMap<FPTRSoftItemPath, int32> LocalDeltaItems;


	/**
	 *	Applies B to A
	 */
	UFUNCTION()
	static TMap<FPTRSoftItemPath, int32> MergeMaps(const TMap<FPTRSoftItemPath, int32> &A, const TMap<FPTRSoftItemPath, int32> &B);


};
