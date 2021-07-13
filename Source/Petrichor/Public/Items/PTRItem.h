// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "Engine/DataAsset.h"
#include "PTRItem.generated.h"



UCLASS(ClassGroup=(PTR), Category="Petrichor|Items")
class UPTRItem : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    // Default CTR
    UPTRItem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /**
     *  Reference this in your asset manager
     */
    UPROPERTY(EditAnywhere, blueprintReadOnly, Category="System")
    FPrimaryAssetType ItemType;

    /**
     *  The unique name for this item
     */
    UPROPERTY(VisibleAnywhere, blueprintReadOnly, Category="System")
    FName InternalName;

    // uniqueID used for referencing this
    virtual FPrimaryAssetId GetPrimaryAssetId() const override
    {
        return FPrimaryAssetId(ItemType, InternalName);
    }

protected:

    /** Name displayed to the user. */
    UPROPERTY(EditAnywhere, blueprintReadOnly, Category="Info")
    FText DisplayName;

    /** Extra Info we can display to the user. */
    UPROPERTY(EditAnywhere, blueprintReadOnly, Category="Info")
    FText Description;




};