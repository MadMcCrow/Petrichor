// Copyright © Noé Perard-Gayot 2021.

#include "Items/PTRItem.h"




UPTRItem::UPTRItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	UpdateItemInternal();
}


void UPTRItem::PreSave(const ITargetPlatform* TargetPlatform)
{
#if WITH_EDITOR
	UpdateItemInternal();
#endif WITH_EDITOR
}

void UPTRItem::UpdateItemInternal()
{
	InternalName = GetFName();
	AssetType = FName("Item");
}