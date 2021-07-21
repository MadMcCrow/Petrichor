// Copyright © Noé Perard-Gayot 2021.

#include "Attributes/PTRAttributeArmor.h"

#define LOCTEXT_NAMESPACE "PTR"

UPTRAttributeArmor::UPTRAttributeArmor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	InternalName = FName("Armor");
	DisplayName = LOCTEXT("Armor", "Armor");
}

#undef LOCTEXT_NAMESPACE