// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PTRGameContext.generated.h"

/**
 *	Context for GameEvents
 */
UCLASS(BlueprintType, DefaultToInstanced, ClassGroup=(PTR), Category="Petrichor")
class PETRICHOR_API UPTRGameContext : public UObject
{
	GENERATED_BODY()

public:

	// CTR
	UPTRGameContext( const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());

};