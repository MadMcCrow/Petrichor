// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#include "Actors/PTRInteractionActor.h"

#include "GameEvent/PTRGameEvent.h"
#include "Net/UnrealNetwork.h"

APTRInteractionActor::APTRInteractionActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsDisabled = false;
	bReplicates = true;
}

void APTRInteractionActor::SetIsDisabled(bool bNewIsDisabled)
{
	if (HasAuthority())
	{
		bIsDisabled = bNewIsDisabled;
	}
}

bool APTRInteractionActor::GetIsDisabled() const
{
	return bIsDisabled;
}

void APTRInteractionActor::StartInteraction(AActor * Target)
{
	if (!bIsDisabled)
	{
		// Game event will manually handle authority and what's not
		if (InteractionGameEvent)
		{
			InteractionGameEvent->StartEvent(this , Target);
		}
	}
}

void APTRInteractionActor::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	DOREPLIFETIME(APTRInteractionActor, bIsDisabled);
}
