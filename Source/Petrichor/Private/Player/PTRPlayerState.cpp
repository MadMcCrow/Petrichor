// Copyright © Noé Perard-Gayot 2021.


#include "Player/PTRPlayerState.h"
#include "Engine/AssetManager.h"
#include "Items/PTRInventoryComponent.h"

FName APTRPlayerState::InventoryComponentName	= TEXT("InventoryComponent");

APTRPlayerState::APTRPlayerState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerInventory		= ObjectInitializer.CreateDefaultSubobject<UPTRInventoryComponent>(this, InventoryComponentName, true);
}

void APTRPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ROLE_Authority)
	{
		if (const UDataTable* ItemDataTable = StartingItem.LoadSynchronous())
		{
			TArray<FPTRInventoryItem*>	StartingItemsPtr;
			TSet<FPTRInventoryItem>		StartingItems;

			ItemDataTable->GetAllRows<FPTRInventoryItem>(TEXT("APTRPlayerState : Getting Starting items"), StartingItemsPtr);

			UAssetManager* Manager = UAssetManager::GetIfValid();
			if (!Manager)
			{
				return;
			}

			for (auto ItemItr : StartingItemsPtr)
			{
				if (ItemItr)
				{
					if (!Manager->GetPrimaryAssetPath(ItemItr->AssetId).IsNull())
					{
						StartingItems.Add(*ItemItr);
					}
				}
			}
			// init the inventory
			PlayerInventory->InitInventory(StartingItems);
		}
	}
}