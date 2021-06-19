// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "PTRWeaponTypes.generated.h"


/** This is used for animation and visual purposes mostly */
UENUM(BlueprintType)
enum class EPTRFireMode : uint8
{
	Primary		UMETA(DisplayName="Primary"),
	Secondary	UMETA(DisplayName="Secondary")
};

/** This is used for animation and visual purposes mostly */
UENUM(BlueprintType)
enum class EPTRWeaponStance : uint8
{
	None		UMETA(DisplayName="No Weapon"),
	Holster		UMETA(DisplayName="holster"),
	Disable		UMETA(DisplayName="lower down"),
	Idle		UMETA(DisplayName="draw"),
	Primary		UMETA(DisplayName="Primary attack"),
	Secondary	UMETA(DisplayName="Secondary attack"),
	Reload		UMETA(DisplayName="Reload")
};