// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"

#include "Items/PTRPickupItem.h"
#include "PTRAmmunition.generated.h"


/**
 *	Ammunition are just a default class storing information about that ammo
 *	They are used to find out if you have ammo in your inventory
 */
UCLASS(Abstract)
class PETRICHOR_API UPTRAmmunition : public UPTRPickupItem
{
	GENERATED_BODY()

protected:

};