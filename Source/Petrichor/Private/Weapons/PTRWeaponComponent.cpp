// Copyright © Noé Perard-Gayot 2021.


#include "Weapons/PTRWeaponComponent.h"

#include "Net/UnrealNetwork.h"


UPTRWeaponComponent::UPTRWeaponComponent() : Super()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPTRWeaponComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetIsReplicated(true);
}

void UPTRWeaponComponent::HolsterWeapon()
{

}

void UPTRWeaponComponent::DrawWeapon()
{

}

void UPTRWeaponComponent::FirePrimary()
{

}

void UPTRWeaponComponent::FireSecondary()
{

}


bool UPTRWeaponComponent::IsWeaponDrawn()
{
	return	WeaponStance == EPTRWeaponStance::Idle		||
			WeaponStance == EPTRWeaponStance::Primary	||
			WeaponStance == EPTRWeaponStance::Secondary;
}

void UPTRWeaponComponent::SetWeaponMeshes(USkeletalMeshComponent* FPSWeapon, USkeletalMeshComponent* TPSWeapon)
{
	FirstPersonWeapon = FPSWeapon;
	if (FirstPersonWeapon)
	{
		USkeletalMesh* WeaponMesh = GetWeapon()->WeaponMesh.Get();
		if (WeaponMesh)
		{
			FirstPersonWeapon->SetSkeletalMesh(WeaponMesh, true);
		}

	}

	ThirdPersonWeapon = TPSWeapon;
	if (ThirdPersonWeapon)
	{
		USkeletalMesh* WeaponMesh = GetWeapon()->WeaponMesh.Get();
		if (WeaponMesh)
		{
			ThirdPersonWeapon->SetSkeletalMesh(WeaponMesh, true);
		}
	}
}

void UPTRWeaponComponent::SetWeapon(TSubclassOf<UPTRWeapon> NewWeaponClass)
{
	// make it network ready
	if (GetOwnerRole() == ROLE_Authority)
	{
		Net_SetWeapon(NewWeaponClass);
	}
}

void UPTRWeaponComponent::OnFire(EPTRFireMode FireMode)
{
	Net_Fire(FireMode);
	switch (FireMode)
	{
	case EPTRFireMode::Primary:
		Net_UpdateWeaponStance(EPTRWeaponStance::Primary);
		break;
	case EPTRFireMode::Secondary:
		Net_UpdateWeaponStance(EPTRWeaponStance::Secondary);
		break;
	default: ;
	}
}

void UPTRWeaponComponent::Net_Fire_Implementation(EPTRFireMode FireMode)
{
	// Update Weapon stance on server
	if (GetOwnerRole() == ROLE_Authority)
	{
		// Do the actual firing ? Check first ?
	}
}

void UPTRWeaponComponent::Net_UpdateWeaponStance_Implementation(EPTRWeaponStance NewWeaponStance)
{
	// Update Weapon stance on server
	if (GetOwnerRole() == ROLE_Authority)
	{
		// todo : implement more safety ?
		WeaponStance = NewWeaponStance;
	}
}

void UPTRWeaponComponent::Net_SetWeapon_Implementation(TSubclassOf<UPTRWeapon> NewWeaponClass)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		// todo : implement more safety ?
		WeaponClass = NewWeaponClass;
	}
}

void UPTRWeaponComponent::OnRep_WeaponClass()
{
	WeaponCDO = WeaponClass.GetDefaultObject();
}

void UPTRWeaponComponent::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME( UPTRWeaponComponent, WeaponStance );
	DOREPLIFETIME( UPTRWeaponComponent, WeaponClass );
}