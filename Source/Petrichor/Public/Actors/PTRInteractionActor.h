// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PTRInteractionActor.generated.h"


UCLASS(ClassGroup=(PTR), config=Game, Category="Petrichor")
class APTRInteractionActor : public AActor
{
    GENERATED_BODY()

public:

    APTRInteractionActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:


    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Interaction")
    virtual void StartInteraction(AActor * Target);


    /** Game Event triggered on Interaction */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
    class UPTRGameEvent* InteractionGameEvent;

};
