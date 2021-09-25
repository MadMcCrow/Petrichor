// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#include "Items/PTRInventoryComponent.h"
#include "Engine/AssetManager.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY(LogPTRInventory);

UPTRInventoryComponent::UPTRInventoryComponent(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, bUseMaxDelta(false)
, MaxLocalDelta(5)
, Items()
, LocalDeltaItems()
{
}

bool UPTRInventoryComponent::AddItem(const FPTRSoftItemPath& Item, int32 Count)
{
	if (Item.IsNull() || Count <= 0)
	{
		return false;
	}

	UpdateItem(Item, Count);
	return true;
}

bool UPTRInventoryComponent::RemoveItem(const FPTRSoftItemPath& Item, int32 Count)
{
	if (Item.IsNull() || Count <= 0)
	{
		return false;
	}

	UpdateItem(Item, -1 * Count);
	return true;
}

int32 UPTRInventoryComponent::ItemCount(const FPTRSoftItemPath& Item, bool bSynchronisedOnly /*= false */) const
{
	if (Item.IsNull())
	{
		return 0;
	}

	// Choose set to use, then find ID in set
	const TSet<FPTRInventoryItem> Inventory = bSynchronisedOnly ? Items : ApplyChanges(Items, LocalDeltaItems);  
	const auto ItemSetId = Inventory.FindId(FPTRInventoryItem(Item,0));
	if (ItemSetId.IsValidId())
	{
		return Inventory[ItemSetId].GetCount();
	}
	return 0;
}

bool UPTRInventoryComponent::HasItem(const FPTRSoftItemPath& Item, bool bSynchronisedOnly /*= false */)const
{
	return ItemCount(Item, bSynchronisedOnly) > 0;
}

TArray<FPTRSoftItemPath> UPTRInventoryComponent::GetItems(bool bSynchronisedOnly /*= false */) const
{
	TArray<FPTRInventoryItem> Inventory;
	if (bSynchronisedOnly)
	{
		Inventory=  Items.Array();
	}
	else
	{
		Inventory =  ApplyChanges(Items,LocalDeltaItems).Array();
	}

	TArray<FPTRSoftItemPath> ItemPaths;
	ItemPaths.Reserve(Inventory.Num());
	for(auto ArrItr = Inventory.CreateConstIterator(); ArrItr;++ArrItr)
	{
		ItemPaths.Add(ArrItr->GetPath());
	}
	return ItemPaths;
}

void UPTRInventoryComponent::InitInventory(const TMap<FPTRSoftItemPath, int32> &InitItems)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		for (auto ItemItr : InitItems)
		{
			UpdateItem(ItemItr.Key, ItemItr.Value, true);
		}
	}
}

void UPTRInventoryComponent::UpdateItem(const FPTRSoftItemPath& Item, int32 Count, bool bForceSync /*= false*/)
{
	// add change to list of changes
	const int32 NewIdx = LocalDeltaItems.Add(FPTRInventoryItem(Item, Count));
	
	// Broadcast with new count
	OnLocalUpdateItem.Broadcast(Item, ItemCount(Item));

	// Sync if necessary
	if (bForceSync || LocalDeltaItems.Num() > MaxLocalDelta)
	{
		if (GetOwnerRole() == ROLE_Authority)
		{
			// directly call server function
			Net_RequestSyncInventory_Implementation();
		}
		else
		{
			Net_RequestSyncInventory();
		}
	}

}

void UPTRInventoryComponent::Net_RequestSyncInventory_Implementation()
{
	// Implementation should only run on server
	ensureMsgf(GetOwnerRole() == ROLE_Authority, TEXT("Function Net_RequestSyncInventory_Implementation should always be run on Server"));
	Items = ApplyChanges(Items,LocalDeltaItems);
	Net_SyncInventory(LocalDeltaItems);
	LocalDeltaItems.Empty();
}

void UPTRInventoryComponent::Net_SyncInventory_Implementation(const TArray<FPTRInventoryItem> &Changes)
{
	if (GetOwnerRole() != ROLE_Authority)
	{
		LocalDeltaItems.Empty();
		Items = ApplyChanges(Items,Changes);
	}
}

TSet<FPTRInventoryItem> UPTRInventoryComponent::ApplyChanges(const TSet<FPTRInventoryItem> &Base, const TArray<FPTRInventoryItem> &Changes)
{
	// copy base
	TSet<FPTRInventoryItem> Retval = Base;
	// aplly changes 
	for (const auto& ChangeItr : Changes)
	{
		// modify already present value
		if (Base.Contains(ChangeItr))
		{
			Retval[Retval.FindId(ChangeItr)].UpdateCount(ChangeItr.GetCount());
		}
		else 
		{
			ensureMsgf(ChangeItr.GetCount() >0, TEXT("UPTRInventoryComponent: trying to remove item while not in base"));
			Retval.Add(FPTRInventoryItem(ChangeItr));
		}
	}
	return Retval;
}
