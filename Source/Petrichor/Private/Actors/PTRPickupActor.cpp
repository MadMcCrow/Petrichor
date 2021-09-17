// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#include "Actors/PTRPickupActor.h"
#include "Characters/PTRCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

FName APTRPickupActor::CollisionComponentName	= TEXT("CollisionBox");
FName APTRPickupActor::MeshComponentName		= TEXT("StaticMesh");

APTRPickupActor::APTRPickupActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CollisionComponent	= ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, CollisionComponentName);
	MeshComponent		= ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, MeshComponentName);

	RootComponent = CollisionComponent;
	MeshComponent->SetupAttachment(RootComponent);

	CollisionComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &APTRPickupActor::OnBeginOverlap);

}

void APTRPickupActor::SetIsDisabled(bool bNewIsDisabled)
{
	Super::SetIsDisabled(bNewIsDisabled);
	SetActorHiddenInGame(GetIsDisabled());
}

void APTRPickupActor::StartInteraction(AActor* Target)
{
	Super::StartInteraction(Target);
	SetIsDisabled(true);
	if (HasAuthority())
	{
		if (bShouldRespawn)
		{
			FTimerDelegate RespawnDel;
			RespawnDel.BindWeakLambda(this, [this](){SetIsDisabled(false);});
			GetWorldTimerManager().SetTimer(RespawnTimerHandle, RespawnDel, fRespawnDelay, false);
		}
	}
}

void APTRPickupActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APTRCharacter* Char = Cast<APTRCharacter>(OtherActor))
	{
		StartInteraction(Char);
	}
}
