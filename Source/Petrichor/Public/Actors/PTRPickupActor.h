// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "CoreMinimal.h"

#include "PTRInteractionActor.h"
#include "PTRPickupActor.generated.h"

/**
*	@class APTRPickupActor {public:APTRInteractionActor};
*
*	@brief An actor to start a game event based on collision with a character
*
*	@todo This should actually be handled with a "looping" game event and a component for interaction
*/
UCLASS(ClassGroup=(PTR), config=Game, Category="Petrichor|Items")
class APTRPickupActor : public APTRInteractionActor
{
    GENERATED_BODY()

public:
    // CTR
    APTRPickupActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    // <APTRInteractionActor api>
    virtual void SetIsDisabled(bool bNewIsDisabled) override;
    virtual void StartInteraction(AActor * Target) override;
    // </APTRInteractionActor api>

protected:

    /** will this actor disable itself for some timer and then come back ?  */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction", meta = (DisplayName = "Should respawn after interaction ?"))
    bool bShouldRespawn = false;

    /** time for wich this actor will be disabled  */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction", meta = (EditCondition = "bShouldRespawn", DisplayName = "Delay before respawn"))
    float fRespawnDelay = 10.f;

private:

    /** Timer for respawning */
    UPROPERTY(Transient)
    FTimerHandle RespawnTimerHandle;

private:

    /** Mesh Component */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* MeshComponent;


    /** Collision Component */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
    class UBoxComponent* CollisionComponent;

    /** Collision Handling function */
    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);




public:
	static FName CollisionComponentName;
    static FName MeshComponentName;
};
