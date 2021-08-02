// Copyright © Noé Perard-Gayot 2021.


#include "Weapons/PTRWeapon.h"

#include "GameEvent/PTRGameEvent.h"

void UPTRWeapon::FirePrimary_Implementation(AActor* Instigator)
{
	if (PrimaryGameEvent)
	{
		PrimaryGameEvent->StartEvent(Instigator, nullptr);
	}
}

void UPTRWeapon::FireSecondary_Implementation(AActor* Instigator)
{
	if (SecondaryGameEvent)
	{
		SecondaryGameEvent->StartEvent(Instigator, nullptr);
	}
}

TSoftObjectPtr<UAnimSequenceBase> UPTRWeapon::GetAnimationAsset(EPTRCharacterViewType View,	EPTRWeaponStance Stance) const
{
	switch (View)
	{
		case EPTRCharacterViewType::FirstPerson:
			if (const auto Found = PlayerAnimations.Find(Stance))
				return *Found;
			return TSoftObjectPtr<UAnimSequenceBase>();
		case EPTRCharacterViewType::ThirdPerson:
			if (const auto Found = CharacterAnimations.Find(Stance))
				return *Found;
			return TSoftObjectPtr<UAnimSequenceBase>();
	}
	return TSoftObjectPtr<UAnimSequenceBase>();
}

TSoftObjectPtr<UAnimSequenceBase> UPTRWeapon::GetMeshAnimation(EPTRWeaponStance Stance) const
{
	if (const auto Found = WeaponAnimations.Find(Stance))
		return *Found;
	return TSoftObjectPtr<UAnimSequenceBase>();
}
