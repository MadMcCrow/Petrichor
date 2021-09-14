// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "GameEvent/PTRGameEvent.h"

DEFINE_LOG_CATEGORY(LogPTRGameEvent);

// CTR
UPTRGameEvent::UPTRGameEvent( const FObjectInitializer &ObjectInitializer)
: Super(ObjectInitializer)
, bReplicatedEvent(true)
, bClientRunEvent(true)
, bServerRunEvent(true)
, bIsRunning(false)
{

}

void UPTRGameEvent::StartEvent(AActor* Source, AActor* Target)
{
	if (!CanCallEvent())
	{
		return;
	}
	#if WITH_EDITOR
		UE_LOG(LogPTRGameEvent, Display, TEXT("Start Event %s"), *GetName());
	#endif // WITH_EDITOR

	if (!bReplicatedEvent)
	{
		OnEventStart();
		return;
	}


	if (Source->GetLocalRole() == ENetRole::ROLE_Authority)
	{
		// call server implementation (no need to go through networking to call ourselves)
		Net_StartServerEvent_Implementation(Source, Target);
	}
	else
	if (Source->GetLocalRole() == ENetRole::ROLE_AutonomousProxy)
	{
		// directly call Client function
		OnClientEventStart();
		// Check that we actually should allow Client to ask server for event
		if (bClientRunEvent)
		{
			// Call server event so that everyone gets the replicated event
			Net_StartServerEvent(Source, Target);
		}
	}
}

void UPTRGameEvent::EndEvent(bool bEndSuccess)
{
	if (!bReplicatedEvent)
	{
		OnEventEnd();
		return;
	}

	if (GetSource()->GetLocalRole() == ENetRole::ROLE_Authority)
	{
		if (bServerRunEvent)
		{
			Net_EndClientEvent_Implementation(bEndSuccess);
		}
		Net_EndClientEvent(bEndSuccess);
	}



}

bool UPTRGameEvent::CanCallEvent_Implementation() const
{
	return true;
}

void UPTRGameEvent::OnServerEventStart_Implementation()
{
}

void UPTRGameEvent::OnClientEventStart_Implementation()
{
}

void UPTRGameEvent::OnOwningClientEventStart_Implementation()
{
}

void UPTRGameEvent::OnEventStart_Implementation()
{
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

bool UPTRGameEvent::IsRunning() const
{
	return bIsRunning;
}

bool UPTRGameEvent::IsSuccess() const
{
	return bIsSuccess;
}

void UPTRGameEvent::Net_StartServerEvent_Implementation(AActor* Source, AActor* Target)
{
	Instigator	= Source;
	TargetActor	= Target;
	check(GetLocalRole() == ROLE_Authority)
	// Call events on Server
	OnServerEventStart();
	// we also are owning client
	OnOwningClientEventStart();
	// call main event if we're allowed
	if (bServerRunEvent)
	{
		OnEventStart();
	}
	// broadcast event to everyone
	Net_StartClientEvent(Source,Target); // broadcast to everyone
}

void UPTRGameEvent::Net_StartClientEvent_Implementation(AActor* Source, AActor* Target)
{
	// server should have already done it's part
	if (GetLocalRole() != ROLE_Authority)
	{
		Instigator	= Source;
		TargetActor	= Target;
		OnClientEventStart();
		// if we're the owning client, call our own event
		if (GetLocalRole() == ROLE_AutonomousProxy)
		{
			OnOwningClientEventStart();
		}
		// run main event on client too
		if (bClientRunEvent)
		{
			OnEventStart();
		}
	}
}


inline void UPTRGameEvent::Net_EndClientEvent_Implementation(bool bEndSuccess)
{
	if (GetLocalRole() != ROLE_Authority)
	{
		bIsSuccess = bEndSuccess;
		OnEventEnd();
	}
}

ENetRole UPTRGameEvent::GetLocalRole() const
{
	if (Instigator)
	{
		return Instigator->GetLocalRole();
	}
	return ROLE_None;
}

ENetRole UPTRGameEvent::GetRemoteRole() const
{
	if (Instigator)
	{
		return Instigator->GetRemoteRole();
	}
	return ROLE_None;
}
