// Copyright © Noé Perard-Gayot 2021.

#include "Attributes/PTRAttributeItem.h"

UPTRAttributeItem::UPTRAttributeItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

FPrimaryAssetId UPTRAttributeItem::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(StaticClass()->GetFName(),InternalName);
}