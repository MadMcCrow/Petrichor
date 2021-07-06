// Copyright © Noé Perard-Gayot 2021.


#include "Weapons/PTRWeapon.h"

UPTRWeapon* UPTRWeapon::GetWeaponObject(const UObject* Outer, TSubclassOf<UPTRWeapon> WeaponClass)
{
	if (WeaponClass != nullptr)
	{
		// For now we use CDO, but we could easily shift away from this and use assets instead.
		return Cast<UPTRWeapon>(WeaponClass->GetDefaultObject(true));
	}
	return nullptr;
}