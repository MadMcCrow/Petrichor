// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "PTRItem.h"
#include "PTRPickupItem.generated.h"



UCLASS(ClassGroup=(PTR), config=Game, Category="Petrichor|Items")
class UPTRPickupItem : public UPTRItem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, Category="Item|Pickup")
    void OnPickup();
    virtual void OnPickup_Implementation();
};