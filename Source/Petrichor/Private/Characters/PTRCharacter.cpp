// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/PTRCharacter.h"
#include "Weapons/PTRWeaponComponent.h"

FName APTRCharacter::WeaponComponentName= TEXT("WeaponComponent");

APTRCharacter::APTRCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	WeaponComponent = ObjectInitializer.CreateDefaultSubobject<UPTRWeaponComponent>(this, WeaponComponentName);
}

void APTRCharacter::AddWeapon(TSubclassOf<UPTRWeapon> Weapon)
{
}