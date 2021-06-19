// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "PTRAmmunition.generated.h"


/**
 *	Ammunition are just a default class storing information about that ammo
 *	They are used to find out if you have ammo in your inventory
 */
UCLASS(Abstract, EditInlineNew)
class PETRICHOR_API UPTRAmmunition : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

};