// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "Items/PTRItem.h"
#include "PTRAttributeItem.generated.h"

UCLASS(ClassGroup=(PTR), Abstract, minimalapi, Category="PTR|Attribute")
class UPTRAttributeItem : public UPTRItem
{
	GENERATED_BODY()

public:
	UPTRAttributeItem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


};