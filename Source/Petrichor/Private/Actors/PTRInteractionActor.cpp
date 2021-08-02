// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

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
