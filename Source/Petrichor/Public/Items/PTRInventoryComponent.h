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
 *	@struct FPTRInventoryItem
 *	This replaces TMap as TMap does not bode well with networking (at least on linux)
 */
USTRUCT(BlueprintType, Category="Petrichor|Items")
struct FPTRInventoryItem
{
    GENERATED_BODY()

	// Good CTR
    FPTRInventoryItem(const FPTRSoftItemPath& Item, int32 Num = 0)
    : ItemPath(Item)
    , Count(Num)
    {}

	// default CTR
    FPTRInventoryItem()
    : ItemPath(FPTRSoftItemPath())
    , Count(0)
    {}

protected:

    /** What Item */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FPTRSoftItemPath ItemPath;

    /** How many */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Count;

public:

    // <getters>

    FORCEINLINE const FPTRSoftItemPath& GetPath() const {return ItemPath;}
    FORCEINLINE const int32& GetCount() const           {return Count;}
    FORCEINLINE TPair<FPTRSoftItemPath, int32> GetPair() const {return TPair<FPTRSoftItemPath, int32>(ItemPath, Count);}

    // </getters>

	// <setters>
    FORCEINLINE void SetCount(int32 NewCount)           {Count = NewCount;}
  	FORCEINLINE void UpdateCount(int32 Offset)           {Count += Offset;}
	// </setters>
    
	// <back-end>

    //X& operator+=(const X& rhs)


    /** Serializer to simplify it's serialisation */
    bool Serialize(FArchive& Ar)
    {
		if (Ar.IsSaving())
		{
			FString Path = ItemPath.ToSoftPath().ToString();
        	Ar << Path;
		}
		else
		{
			FString Path;
			Ar << Path;
			ItemPath = FSoftObjectPath(Path);
		}
        Ar << Count;
        return true;
    }

    /** Serializer to simplify it's serialisation */
    bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
    {
		Serialize(Ar);
        return true;
    }

    /** Type Hash for use in TSet   */
    friend uint32 GetTypeHash(const FPTRInventoryItem& Item)
    {
        return GetTypeHash(Item.GetPath());
    }

    /** == operator for use in TSet   */
    // TODO : Check if this does not causes issues with counting item
    bool operator==(const FPTRInventoryItem& rhs) const
    {
        return rhs.GetPath() == GetPath();
    }


    // </back-end>

};


// register the serialiser for the Soft Item Path
template<>
struct TStructOpsTypeTraits<FPTRInventoryItem> : public TStructOpsTypeTraitsBase2<FPTRInventoryItem>
{
    enum
    {
        WithSerializer	= true, // might causes errors
        WithNetSerializer	= true,
    };
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
	int32 ItemCount(const FPTRSoftItemPath& Item, bool bSynchronisedOnly = false ) const;

	/**
	 *  ItemCount
	 *  @brief  do we store a certain item
	 *  @return The amount of the item stored, or 0 if not present
	 */
	UFUNCTION(BlueprintPure, Category="Inventory")
	bool HasItem(const FPTRSoftItemPath& Item, bool bSynchronisedOnly = false ) const;

	/**
	*  GetItems
	*  @brief  Getter for the item set.
	*  @param bSynchronisedOnly	 if true, Only return the items has validated by server
	*/
	UFUNCTION(BlueprintPure, Category="Inventory")
	TArray<FPTRSoftItemPath> GetItems(bool bSynchronisedOnly = false) const;


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
	void Net_SyncInventory(const TArray<FPTRInventoryItem>  &Changes);
	virtual void Net_SyncInventory_Implementation(const TArray<FPTRInventoryItem> &Changes);
	virtual bool Net_SyncInventory_Validate(const TArray<FPTRInventoryItem> &Changes) const {return true;}



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
	TSet<FPTRInventoryItem> Items;

	/**
	 *	LocalDeltaItems
	 *	@note all deltas to the Items, not merged
	 *	@brief The locally changes in Items
	 */
	UPROPERTY(Transient, VisibleAnywhere, Category="Inventory")
	TArray<FPTRInventoryItem> LocalDeltaItems;


	/**
	 *	Applies B to A
	 */
	UFUNCTION()
	static TSet<FPTRInventoryItem> ApplyChanges(const TSet<FPTRInventoryItem> &Base, const TArray<FPTRInventoryItem> &Changes);


};
