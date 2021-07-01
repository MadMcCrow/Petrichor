// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "Engine/DataAsset.h"
#include "PTRItem.generated.h"



UCLASS(Category="Petrichor|Items")
class UPTRItem : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, blueprintReadOnly, Category="System")
    FPrimaryAssetType ItemType;


    virtual FPrimaryAssetId GetPrimaryAssetId() const override
    {
        return FPrimaryAssetId(ItemType, GetFName());
    }

protected:

    /** Name displayed to the user. */
    UPROPERTY(EditAnywhere, blueprintReadOnly, Category="Info")
    FText DisplayName;




};