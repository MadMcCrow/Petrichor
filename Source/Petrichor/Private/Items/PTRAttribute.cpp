// Copyright © Noé Perard-Gayot 2021.


#include "Items/PTRAttribute.h"


UPTRAttribute::UPTRAttribute(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	InternalName = AttributeName;
}