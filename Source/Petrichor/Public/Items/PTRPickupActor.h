// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PTRPickupActor.generated.h"


UCLASS(ClassGroup=(PTR), config=Game, Category="Petrichor|Items")
class APTRPickupActor : public AActor
{
    GENERATED_BODY()

public:

    APTRPickupActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
    // The Item to collect
    UPROPERTY(Transient, VisibleAnywhere, Category="Inventory")
    TSoftObjectPtr<APTRPickupActor> Items;

private:

    /**
     *  Mesh Component
     */
    UPROPERTY(Transient, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* MeshComponent;


    /**
     *  Collision Component
     */
    UPROPERTY(Transient, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    class UBoxComponent* CollisionComponent;

public:
	static FName CollisionComponentName;
    static FName MeshComponentName;
};