// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PTRAIController.generated.h"

/**
 *	Base AI Controller for AI in Petrichor
 */
UCLASS(ClassGroup=(PTR), Category="Petrichor")
class PETRICHOR_API APTRAIController : public AAIController
{
	GENERATED_BODY()

public:

	// CTR
	APTRAIController( const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());
};