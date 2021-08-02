// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "CoreMinimal.h"

#include "PTRInteractionActor.h"
#include "PTRPickupActor.generated.h"

/**
 *  Interaction Actor for Ground pickups
 */
UCLASS(ClassGroup=(PTR), config=Game, Category="Petrichor|Items")
class APTRPickupActor : public APTRInteractionActor
{
    GENERATED_BODY()

public:

    APTRPickupActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

private:

    /**
     *  Mesh Component
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* MeshComponent;


    /**
     *  Collision Component
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    class UBoxComponent* CollisionComponent;

    /** Collision Handling function */
    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:
	static FName CollisionComponentName;
    static FName MeshComponentName;

};
