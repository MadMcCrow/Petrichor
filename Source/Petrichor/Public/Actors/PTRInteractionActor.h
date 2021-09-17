// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PTRInteractionActor.generated.h"

/**
 *	@class APTRInteractionActor {public:AActor};
 *
 *	@brief An actor to start a game event in the world, triggered by the player
 *	@todo Create a component to define interactions (collision, button press, etc)
 */
UCLASS(ClassGroup=(PTR), config=Game, Category="Petrichor")
class APTRInteractionActor : public AActor
{
    GENERATED_BODY()

public:

    // CTR
    APTRInteractionActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** Disable or enable this interaction. by default the interaction is always enabled */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Interaction")
	virtual void SetIsDisabled(bool bNewIsDisabled = true);

	/** get disable status */
	UFUNCTION(BlueprintPure, Category="Interaction")
	bool GetIsDisabled() const;

protected:

    /**
     *  @fn StartInteraction
     *  This will start the Game Event @see InteractionGameEvent
     */
    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Interaction")
    virtual void StartInteraction(AActor * Target);

    /** Game Event triggered on Interaction */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category="Interaction")
    class UPTRGameEvent* InteractionGameEvent;

private:

	/**	if true this interaction wont work */
	UPROPERTY(EditDefaultsOnly, ReplicatedUsing= "SetIsDisabled", Category="Interaction", AdvancedDisplay)
	bool bIsDisabled;

};
