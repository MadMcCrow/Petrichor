// Copyright © Noé Perard-Gayot 2021.

#include "Items/PTRInventoryComponent.h"

#include "Engine/AssetManager.h"
#include "Items/PTRItem.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY(LogPTRInventory);

FPTRInventoryItem::FPTRInventoryItem(const FPTRSoftItemPath &Path, int32 Num): Super(), Count(Num)
{
	if (!Path.IsNull())
	{
		if (UAssetManager* Manager = UAssetManager::GetIfValid())
		{
			AssetId = Manager->GetPrimaryAssetIdForPath(Path);
		}
	}
}

FPTRInventoryItem::FPTRInventoryItem(const TSoftObjectPtr<UPTRItem>& Path, int32 Num)
: FPTRInventoryItem(Path.ToSoftObjectPath(), Num)
{
}

bool FPTRInventoryItem::IsNull() const
{
	return FPTRSoftItemPath(AssetId).IsNull();
}

UPTRInventoryComponent::UPTRInventoryComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Items.Empty();
}

bool UPTRInventoryComponent::AddItem(const FPTRSoftItemPath& Item, int32 Count)
{
	if (Item.IsNull() || Count <= 0)
	{
		return false;
	}
	// Only server can add items, get over it.
	if (GetOwnerRole() == ROLE_Authority)
	{
		// Warning this will load the item
		const int32 NewCount = ItemCount(Item) + Count;
		Net_UpdateItem(FPTRInventoryItem(Item, NewCount));
		return true;
	}
	return false;
}

bool UPTRInventoryComponent::RemoveItem(const FPTRSoftItemPath& Item, int32 Count)
{
	if (Item.IsNull() || Count <= 0)
	{
		return false;
	}

	if (GetOwnerRole() == ROLE_Authority)
	{
		const int32 NewCount = ItemCount(Item) - Count;
		Net_UpdateItem(FPTRInventoryItem(Item, Count));
		return true;
	}
	return false;
}


int32 UPTRInventoryComponent::ItemCount(const FPTRSoftItemPath& Item) const
{
	if (Item.IsNull())
	{
		return 0;
	}

	const auto Key	= FPTRInventoryItem(Item, -1);
	if (const auto FoundItem = Items.FindByHash(GetTypeHash(Key),Key))
	{
		return FoundItem->Count;
	}
	return 0;
}

bool UPTRInventoryComponent::HasItem(const FPTRSoftItemPath& Item) const
{
	return ItemCount(Item) > 0;
}

TSet<FPTRInventoryItem> UPTRInventoryComponent::GetItems() const
{
	return Items;
}

void UPTRInventoryComponent::InitInventory(TSet<FPTRInventoryItem>& InitItems)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		// update server's version
		Items = InitItems;

		for (auto ItemItr : InitItems)
		{
			Net_OnUpdateItem(ItemItr);
		}
	}
}


void UPTRInventoryComponent::Net_UpdateItem_Implementation(const FPTRInventoryItem& Item)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		// Make sure Item is valid :
		 if (!Item.IsNull())
		 {
		 	// check for change first
		 	if (ItemCount(FPTRSoftItemPath(Item.AssetId)) != Item.Count)
		 	{
#if !UE_BUILD_SHIPPING
		 	UE_LOG(LogPTRInventory, Display, TEXT("adding %i %s in %s"), Item.Count, *Item.ToString(), *GetOwner()->GetName());
#endif //UE_BUILD_SHIPPING
		 		Net_OnUpdateItem(Item);
		 	}
		 }
	}
}

bool UPTRInventoryComponent::Net_UpdateItem_Validate(const FPTRInventoryItem& Item) const
{
	return true;
}

void UPTRInventoryComponent::Net_OnUpdateItem_Implementation(const FPTRInventoryItem& ItemKey)
{
	if (ItemKey.Count > 0)
	{
		Items.Emplace(ItemKey);
	}
	else
	{
		if (const auto Item = Items.Find(ItemKey))
		{
			Items.Remove(*Item);
		}
	}
}

bool UPTRInventoryComponent::Net_OnUpdateItem_Validate(const FPTRInventoryItem& ItemKey) const
{
	return true;
}