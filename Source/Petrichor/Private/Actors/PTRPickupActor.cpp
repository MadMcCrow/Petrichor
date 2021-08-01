// Copyright © Noé Perard-Gayot 2021.

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

	// Bind collision to collision handling function
	CollisionComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &APTRPickupActor::OnBeginOverlap);
}

void APTRPickupActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APTRCharacter* Char = Cast<APTRCharacter>(OtherActor))
	{
		StartInteraction(Char);
	}
}