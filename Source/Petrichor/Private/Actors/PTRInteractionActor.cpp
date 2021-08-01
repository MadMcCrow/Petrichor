// Copyright © Noé Perard-Gayot 2021.

#include "Actors/PTRInteractionActor.h"

#include "GameEvent/PTRGameEvent.h"

APTRInteractionActor::APTRInteractionActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void APTRInteractionActor::StartInteraction(AActor * Target)
{
	if (HasAuthority())
	{
		if (InteractionGameEvent)
		{
			InteractionGameEvent->StartEvent(this , Target);
		}
	}
	// TODO :
	// implement Local execution of GameEvent
}