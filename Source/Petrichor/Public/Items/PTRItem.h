// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "Engine/DataAsset.h"
#include "PTRItem.generated.h"



UCLASS(Abstract, ClassGroup=(PTR), Category="Petrichor|Items")
class PETRICHOR_API UPTRItem : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    // Default CTR
    UPTRItem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /**
     *  Reference this in your asset manager
     */
    UPROPERTY(EditAnywhere, blueprintReadOnly, Category="Item|System")
    FPrimaryAssetType ItemType;

    /**
     *  The unique name for this item
     */
    UPROPERTY(VisibleAnywhere, blueprintReadOnly, Category="Item|System")
    FName InternalName;

    // uniqueID used for referencing this
    virtual FPrimaryAssetId GetPrimaryAssetId() const override
    {
        return FPrimaryAssetId(ItemType, InternalName);
    }

protected:

    /** Name displayed to the user. */
    UPROPERTY(EditAnywhere, blueprintReadOnly, Category="Item|Display")
    FText DisplayName;

    /** Extra Info we can display to the user. */
    UPROPERTY(EditAnywhere, blueprintReadOnly, Category="Item|Display")
    FText Description;




};