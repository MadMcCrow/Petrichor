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

int32 UPTRInventoryComponent::ItemCount(const FPTRSoftItemPath& Item) const
{
	if (Item.IsNull())
	{
		return 0;
	}

	if (const auto FoundItem = GetItems().Find(Item))
	{
		return *FoundItem;
	}
	return 0;
}

bool UPTRInventoryComponent::HasItem(const FPTRSoftItemPath& Item) const
{
	return ItemCount(Item) > 0;
}

TMap<FPTRSoftItemPath, int32> UPTRInventoryComponent::GetItems(bool bSynchronisedOnly /*= false */) const
{
	if (bSynchronisedOnly)
	{
		return Items;
	}

	return MergeMaps(Items, LocalDeltaItems);
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
	if (LocalDeltaItems.Contains(Item))
	{
		LocalDeltaItems[Item] += Count;
	}
	else
	{
		LocalDeltaItems.Add(Item, Count);
	}

	OnLocalUpdateItem.Broadcast(Item, LocalDeltaItems[Item]);

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
	Items = MergeMaps(Items,LocalDeltaItems);
	Net_SyncInventory(LocalDeltaItems);
	LocalDeltaItems.Empty();
}

void UPTRInventoryComponent::Net_SyncInventory_Implementation(const TMap<FPTRSoftItemPath, int32> &Changes)
{
	if (GetOwnerRole() != ROLE_Authority)
	{
		LocalDeltaItems.Empty();
		Items = MergeMaps(Items,Changes);
	}
}

TMap<FPTRSoftItemPath, int32> UPTRInventoryComponent::MergeMaps(const TMap<FPTRSoftItemPath, int32> &A, const TMap<FPTRSoftItemPath, int32> &B)
{
	TMap<FPTRSoftItemPath, int32> Retval = A;
	for (TTuple<FPTRSoftItemPath, int> BItemItr : B)
	{
		if (Retval.Contains(BItemItr.Key))
		{
			Retval[BItemItr.Key] += BItemItr.Value;
		}
		else
		{
			if(BItemItr.Value >= 0)
			Retval.Add(BItemItr);
		}
	}
	return Retval;
}
