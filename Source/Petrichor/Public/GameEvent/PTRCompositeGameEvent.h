// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "PTRGameEvent.h"
#include "PTRCompositeGameEvent.generated.h"

/**
 *	EPTRCompositeGameEventPlayMode
 *	Defines how a composite GameEvent plays it's events
 *	@note	We could add Select, Random, etc
 *	@todo	Determine the usefullness of other types
 */
UENUM(BlueprintType, Category="Petrichor|GameEvent")
enum class EPTRCompositeGameEventPlayMode : uint8
{
	Synchronous			 = 0 UMETA(DisplayName="Synchronous",		 Tooltip="Play all events at once"),
	Sequence			 = 1 UMETA(DisplayName="Sequence",			 Tooltip="Play all events in a sequence"),
	SequenceWithFailStop = 2 UMETA(DisplayName="Sequence With Stop", Tooltip="Play all events in a sequence, stop if one fails"),
};

/**
 *	UPTRCompositeGameEvent
 *	A game event that will start a list of GameEvents.
 *	They can be all started at once or back to back.
 *	@todo : This might benefit from a custom editor for GameEvents
 */
UCLASS(ClassGroup=(PTR), Category="Petrichor|GameEvent", DefaultToInstanced, EditInlineNew)
class PETRICHOR_API UPTRCompositeGameEvent : public UPTRGameEvent
{
	GENERATED_BODY()

public:

	// CTR
	UPTRCompositeGameEvent( const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());

	// UPTRGameEvent API
	virtual bool IsRunning() const override;
	virtual void OnEventStart_Implementation() override;
	virtual void OnEventEnd_Implementation() override;
	// \UPTRGameEvent API

protected:
	/**
	 *	GameEvents
	 *	the list of game events to play
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category="GameEvent|Composite")
	TArray<UPTRGameEvent*> GameEvents;

	/**
	 *	GameEvents
	 *	the list of game events to play
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameEvent|Composite")
	EPTRCompositeGameEventPlayMode PlayMode;

private:
	/** Call all events at once */
	void PlaySynchronous();

	/** Call all events, waiting for each to end to start the next */
	void PlaySequence();

	UPROPERTY(Transient, DuplicateTransient)
	int32 SequenceIdx;

};
