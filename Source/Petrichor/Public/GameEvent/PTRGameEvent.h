// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PTRGameEvent.generated.h"

/**
 *	Player State stores Player information. this is transferred between maps.
 */
UCLASS(ClassGroup=(PTR), Category="Petrichor|GameEvent")
class PETRICHOR_API UPTRGameEvent : public UObject
{
	GENERATED_BODY()

public:

	// CTR
	UPTRGameEvent( const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());

};