// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "GameEvent/PTRGameEvent.h"

DEFINE_LOG_CATEGORY(LogPTRGameEvent);

// CTR
UPTRGameEvent::UPTRGameEvent( const FObjectInitializer &ObjectInitializer)
: Super(ObjectInitializer)
, bShouldCallServerOnClient(true)
, bServerShouldTriggerEventOnOwningClient(true)
{

}

void UPTRGameEvent::StartEvent(AActor* Source, AActor* Target)
{
#if WITH_EDITOR
	UE_LOG(LogPTRGameEvent, Display, TEXT("Start Event %s"), *GetName());
#endif // WITH_EDITOR
	// call server and client functions

	if (Source->GetLocalRole() == ENetRole::ROLE_Authority)
	{
		// directly call server
		OnServerEventStart();
		// and call server implementation (no need to go through networking)
		Net_StartServerEvent_Implementation(Source, Target);
	}
	else
	if (Source->GetLocalRole() == ENetRole::ROLE_AutonomousProxy)
	{
		// directly call Client function
		OnClientEventStart();

		// Check that we actually should allow Client to ask server for event
		if (bShouldCallServerOnClient)
		{
			// Call server event so that everyone gets the replicated event
			Net_StartServerEvent(Source, Target);
		}
	}
}

void UPTRGameEvent::EndEvent()
{
	if (GetSource()->GetLocalRole() == ENetRole::ROLE_Authority)
	{
		Net_EndAllEvent();
	}
}

void UPTRGameEvent::OnServerEventStart_Implementation()
{
#if WITH_EDITOR
	UE_LOG(LogPTRGameEvent, Display, TEXT("Game Event %s : Start server Only"), *GetName());
#endif // WITH_EDITOR

}

void UPTRGameEvent::OnClientEventStart_Implementation()
{
#if WITH_EDITOR
	UE_LOG(LogPTRGameEvent, Display, TEXT("Game Event %s : Start client Only"), *GetName());
#endif // WITH_EDITOR
}

void UPTRGameEvent::OnEventStart_Implementation()
{
#if WITH_EDITOR
	UE_LOG(LogPTRGameEvent, Display, TEXT("Game Event %s : Start Multicast replicated"), *GetName());
#endif // WITH_EDITOR
}

void UPTRGameEvent::OnEventEnd_Implementation()
{
}

AActor* UPTRGameEvent::GetSource() const
{
	return Instigator;
}

AActor* UPTRGameEvent::GetTarget() const
{
	return TargetActor;
}

void UPTRGameEvent::Net_StartServerEvent_Implementation(AActor* Source, AActor* Target)
{
	Instigator	= Source;
	TargetActor	= Target;
	// Call event on Server
	Net_StartAllEvent(Source,Target);
}

void UPTRGameEvent::Net_StartAllEvent_Implementation(AActor* Source, AActor* Target)
{
	Instigator	= Source;
	TargetActor	= Target;
	// Call event on all Actors
	if (bServerShouldTriggerEventOnOwningClient || Instigator->GetLocalRole() != ENetRole::ROLE_AutonomousProxy)
	{
		OnEventStart();
	}
}


inline void UPTRGameEvent::Net_EndAllEvent_Implementation()
{
	// Call End Event on all Actors
	OnEventEnd();
}
