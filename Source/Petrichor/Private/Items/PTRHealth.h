// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "Items/PTRAttribute.h"
#include "PTRHealth.generated.h"

/**
 *
 */
UCLASS()
class UPTRHealth : public UPTRAttribute
{
	GENERATED_BODY()

	UPTRHealth(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
	{
		AttributeName	= TEXT("Health");
		DisplayName		=  NSLOCTEXT("Attributes","Health","Health Points");
	}
};