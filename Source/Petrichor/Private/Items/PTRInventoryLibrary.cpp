// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "Items/PTRInventoryLibrary.h"
#include "Items/PTRInventoryComponent.h"
#include "Items/PTRInventoryInterface.h"


UPTRInventoryComponent* UPTRInventoryLibrary::GetInventoryComponent(const AActor* InventoryActor)
{
	if (InventoryActor->Implements<UPTRInventoryInterface>())
	{
		return IPTRInventoryInterface::Execute_GetInventoryComponent(InventoryActor);
	}
	return Cast<UPTRInventoryComponent>(InventoryActor->GetComponentByClass(UPTRInventoryComponent::StaticClass()));
}

bool UPTRInventoryLibrary::ChangeActorItem(const AActor* InventoryActor, FPTRSoftItemPath Item, int32 Count, EPTRItemOperation Operation)
{
	if (auto Inv = GetInventoryComponent(InventoryActor))
	{
		switch (Operation) {
		case EPTRItemOperation::Add:
				return Inv->AddItem(Item, Count);
		case EPTRItemOperation::Remove:
			return Inv->RemoveItem(Item, Count);
		default: ;
		}
	}
	return false;
}

bool UPTRInventoryLibrary::ChangeActorItemAsset(const AActor* InventoryActor, TSoftObjectPtr<UPTRItem> Item, int32 Count, EPTRItemOperation Operation)
{
	return ChangeActorItem(InventoryActor, Item, Count, Operation);
}
