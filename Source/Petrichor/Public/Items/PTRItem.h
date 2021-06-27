// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "Engine/DataAsset.h"
#include "PTRItem.generated.h"



UCLASS(Abstract, Blueprintable, config=Game, Category="Petrichor|Items")
class UPTRItem : public UPrimaryDataAsset
{
    GENERATED_BODY()

protected:

    /** Name displayed to the user. */
    UPROPERTY(EditAnywhere, blueprintReadOnly, Category="Info")
    FText DisplayName;

};