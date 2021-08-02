// Copyright © Noé Perard-Gayot 2021.


#include "Player/PTRPlayerState.h"
#include "Engine/AssetManager.h"
#include "Items/PTRInventoryComponent.h"
#include "Attributes/PTRAttributeComponent.h"

FName APTRPlayerState::InventoryComponentName = TEXT("InventoryComponent");
FName APTRPlayerState::AttributeComponentName = TEXT("AttributeComponent");


APTRPlayerState::APTRPlayerState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerInventory = ObjectInitializer.CreateDefaultSubobject<UPTRInventoryComponent>(
		this, InventoryComponentName, true);
	PlayerAttributes = ObjectInitializer.CreateDefaultSubobject<UPTRAttributeComponent>(
		this, AttributeComponentName, true);
}

void APTRPlayerState::BeginPlay()
{
	Super::BeginPlay();
	if (GetLocalRole() == ROLE_Authority)
	{
		if (PlayerInventory)
		{
			if (const UDataTable* ItemDataTable = Cast<UDataTable>(StartingItem.TryLoad()))
			{
				TArray<FPTRInventoryItem*> StartingItemsPtr;
				TSet<FPTRInventoryItem> StartingItems;

				ItemDataTable->GetAllRows<FPTRInventoryItem>(
					TEXT("APTRPlayerState : Getting Starting items"), StartingItemsPtr);

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
		if (PlayerAttributes)
		{
			if (const UDataTable* AttributesDataTable = Cast<UDataTable>(AttributesDefinition.TryLoad()))
			{
				TArray<FPTRAttributeDefinition> AttributesArray;
				AttributesDataTable->ForeachRow<FPTRAttributeDefinition>(
					TEXT("APTRPlayerState : Getting Attributes"),
					[&AttributesArray](const FName& Key, const FPTRAttributeDefinition& Value)
					{
						AttributesArray.AddUnique(Value);
					});
				PlayerAttributes->InitAttributes(AttributesArray);
			}
		}
	}
}