// Copyright © Noé Perard-Gayot 2021.

#include "Items/PTRPickupActor.h"
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

}