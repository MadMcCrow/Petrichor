// Copyright © Noé Perard-Gayot 2021.

#include "Attributes/PTRAttributeItem.h"
#include "PTRAttributeArmor.generated.h"

UCLASS(ClassGroup=(PTR), minimalapi, NotBlueprintable, Const, Category="PTR|Attribute")
class UPTRAttributeArmor final : public UPTRAttributeItem
{
	GENERATED_BODY()

public:
	UPTRAttributeArmor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};