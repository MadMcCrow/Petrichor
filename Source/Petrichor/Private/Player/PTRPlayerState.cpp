// Copyright © Noé Perard-Gayot 2021.


#include "Player/PTRPlayerState.h"
#include "Items/PTRInventoryComponent.h"

FName APTRPlayerState::InventoryComponentName = TEXT("InventoryComponent");

APTRPlayerState::APTRPlayerState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerInventory = ObjectInitializer.CreateDefaultSubobject<UPTRInventoryComponent>(this, InventoryComponentName, true);
}