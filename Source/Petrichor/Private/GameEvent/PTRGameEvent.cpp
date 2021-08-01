// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "GameEvent/PTRGameEvent.h"

DEFINE_LOG_CATEGORY(LogPTRGameEvent);


UPTRGameEvent::UPTRGameEvent( const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{

}

void UPTRGameEvent::StartEvent(AActor* Source, AActor* Target)
{
#if WITH_EDITOR
	UE_LOG(LogPTRGameEvent, Display, TEXT("Start Event %s"), *GetName());
#endif // WITH_EDITOR
	// call server and client functions
	Net_StartServerEvent(Source, Target);
	Net_StartClientEvent(Source, Target);
}

void UPTRGameEvent::OnServerEventStart_Implementation()
{

}

void UPTRGameEvent::OnClientEventStart_Implementation()
{

}

void UPTRGameEvent::OnEventStart_Implementation()
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
#if WITH_EDITOR
	UE_LOG(LogPTRGameEvent, Display, TEXT("Start Event on server %s"), *GetName());
#endif // WITH_EDITOR

	Instigator	= Source;
	TargetActor	= Target;
	// Call event on Server
	OnServerEventStart();
}

void UPTRGameEvent::Net_StartClientEvent_Implementation(AActor* Source, AActor* Target)
{
#if WITH_EDITOR
	UE_LOG(LogPTRGameEvent, Display, TEXT("Start Event on Client %s"), *GetName());
#endif // WITH_EDITOR

	Instigator	= Source;
	TargetActor	= Target;
	// Call event on Client
	OnClientEventStart();
}

void UPTRGameEvent::Net_StartAllEvent_Implementation(AActor* Source, AActor* Target)
{
#if WITH_EDITOR
	UE_LOG(LogPTRGameEvent, Display, TEXT("Start Event Multicast %s"), *GetName());
#endif // WITH_EDITOR

	Instigator	= Source;
	TargetActor	= Target;
	// Call event on all Actors
	OnEventStart();
}