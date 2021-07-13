// Copyright © Noé Perard-Gayot 2021.

#include "Items/PTRItem.h"

UPTRItem::UPTRItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	InternalName = GetFName();
}