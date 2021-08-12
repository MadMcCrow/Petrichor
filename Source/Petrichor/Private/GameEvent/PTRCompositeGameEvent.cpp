// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#include "GameEvent/PTRCompositeGameEvent.h"

UPTRCompositeGameEvent::UPTRCompositeGameEvent( const FObjectInitializer &ObjectInitializer)
: Super(ObjectInitializer)
{

}

bool UPTRCompositeGameEvent::IsRunning() const
{
	for (auto GE : GameEvents)
	{
		if (GE->IsRunning())
		{
			return true;
		}
	}
	return Super::IsRunning();
}

void UPTRCompositeGameEvent::OnEventStart_Implementation()
{
	Super::OnEventStart_Implementation();
	switch(PlayMode)
	{
	default:
	case EPTRCompositeGameEventPlayMode::Synchronous:
		PlaySynchronous();
		break;
	case EPTRCompositeGameEventPlayMode::Sequence:
	case EPTRCompositeGameEventPlayMode::SequenceWithFailStop:
		SequenceIdx = 0;
		PlaySequence();
		break;
	}
}

void UPTRCompositeGameEvent::OnEventEnd_Implementation()
{
	Super::OnEventEnd_Implementation();
	switch(PlayMode)
	{
	default:
	case EPTRCompositeGameEventPlayMode::Synchronous:
		return;
	case EPTRCompositeGameEventPlayMode::SequenceWithFailStop:
		if(!IsSuccess())
		{
			SequenceIdx = 0;
			return;
		}
		// FALLTHROUGH !
	case EPTRCompositeGameEventPlayMode::Sequence:
		PlaySequence();
		break;
	}

}

void UPTRCompositeGameEvent::PlaySynchronous()
{
	for (auto GE : GameEvents)
	{
		if (GE != nullptr)
		{
			GE->StartEvent(GetSource(), GetTarget());
		}
	}
}

void UPTRCompositeGameEvent::PlaySequence()
{
	if (GameEvents.IsValidIndex(SequenceIdx))
	{
		GameEvents[SequenceIdx]->OnGameEventEnd.AddUniqueDynamic(this, &UPTRCompositeGameEvent::EndEvent);
		GameEvents[SequenceIdx]->StartEvent(GetSource(), GetTarget());
		SequenceIdx++; // NEXT !
	}
	else
	{
		// Reached the end !
		EndEvent(true);
	}
}
