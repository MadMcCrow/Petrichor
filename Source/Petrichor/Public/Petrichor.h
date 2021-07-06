// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"


/**
 *	This File contains the widely used Types in Petrichor
 *
 *
 */

/**
 *	Simple enum to differentiate FP and TP views
 *	Used in Animation instances, Weapons and characters
 */
UENUM(BlueprintType)
enum class EPTRCharacterViewType : uint8
{
	FirstPerson		UMETA(DisplayName="FirstPerson Arms"),
	ThirdPerson		UMETA(DisplayName="Whole Body Animations")
};


/**
 *	Primary fire is left click traditionally, Secondary is right click.
 *	This is used for animation and visual purposes as well as input
 */
UENUM(BlueprintType)
enum class EPTRFireMode : uint8
{
	Primary		UMETA(DisplayName="Primary"),
	Secondary	UMETA(DisplayName="Secondary")
};

/**
*	Primary fire is left click traditionally, Secondary is right click.
*	This is used for weapon animation and visual purposes : Anim Instances and assets
*/
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