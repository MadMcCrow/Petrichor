// Copyright © Noé Perard-Gayot 2021.

#include "PTRAttributeHealth.h"

#define LOCTEXT_NAMESPACE "PTR"

UPTRAttributeHealth::UPTRAttributeHealth(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	InternalName = FName("Health");
	DisplayName = LOCTEXT("Health", "Health");
}

#undef LOCTEXT_NAMESPACE