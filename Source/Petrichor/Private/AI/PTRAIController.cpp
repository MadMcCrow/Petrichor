// Copyright © Noé Perard-Gayot 2021.

#include "AI/PTRAIController.h"


APTRAIController::APTRAIController( const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	bWantsPlayerState = true;
}