// Copyright © Noé Perard-Gayot 2021.

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


    /** */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
    class UPTRGameEvent* InteractionGameEvent;

};