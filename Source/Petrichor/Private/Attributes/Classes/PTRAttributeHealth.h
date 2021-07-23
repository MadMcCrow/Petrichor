// Copyright © Noé Perard-Gayot 2021.

#include "Attributes/PTRAttributeItem.h"
#include "PTRAttributeHealth.generated.h"

UCLASS(ClassGroup=(PTR), minimalapi, NotBlueprintable, Const, Category="PTR|Attribute")
class UPTRAttributeHealth final : public UPTRAttributeItem
{
	GENERATED_BODY()

public:
	UPTRAttributeHealth(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};