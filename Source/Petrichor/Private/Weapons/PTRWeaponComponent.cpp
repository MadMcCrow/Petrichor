// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.


#include "Weapons/PTRWeaponComponent.h"

#include "Items/PTRInventoryComponent.h"
#include "Items/PTRInventoryInterface.h"
#include "Net/UnrealNetwork.h"


UPTRWeaponComponent::UPTRWeaponComponent() : Super()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPTRWeaponComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetIsReplicated(true);

	if (auto Inv = GetInventoryComponent())
	{
		Inv->OnLocalUpdateItem.AddUniqueDynamic(this, &UPTRWeaponComponent::OnInventoryChange);
	}

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
	TSoftObjectPtr<USkeletalMesh> WeaponMesh;
	if (GetWeapon())
	{
		WeaponMesh = GetWeapon()->GetMesh();
	}

	FirstPersonWeapon = FPSWeapon;
	if (FirstPersonWeapon)
	{
		FirstPersonWeapon->SetSkeletalMesh(WeaponMesh.Get(), true);
	}

	ThirdPersonWeapon = TPSWeapon;
	if (ThirdPersonWeapon)
	{
		ThirdPersonWeapon->SetSkeletalMesh(WeaponMesh.Get(), true);

		// update master pose component
		if (FirstPersonWeapon)
			ThirdPersonWeapon->SetMasterPoseComponent(FirstPersonWeapon, true);
	}

}

void UPTRWeaponComponent::SetWeapon(TSoftObjectPtr<UPTRWeapon> NewWeapon)
{
	// whether we are server or active client, we're gonna do all the switching
	// when server reaches final decision, we will
	if (GetOwnerRole() == ROLE_Authority)
	{
		// Update Weapon for player
		if (WeaponItems.Contains(NewWeapon) && !NewWeapon.IsNull())
		{
			// this will trigger on Rep
			ActiveWeapon = NewWeapon.Get();

			// call multicast : (Is it necessary ?)
			Net_OnSetWeapon(NewWeapon);
		}
	}

	// we're not server but we're gonna do it for ourselves
	if (GetOwnerRole() == ROLE_AutonomousProxy)
	{
		// call server function
		Net_SetWeapon(NewWeapon);

		// in the meantime we shall do it ourselves
		if (WeaponItems.Contains(NewWeapon) && !NewWeapon.IsNull())
		{
			// this will trigger on Rep
			ActiveWeapon = NewWeapon.Get();
			OnWeaponSet();
		}
	}
}

void UPTRWeaponComponent::AddWeapon(TSoftObjectPtr<UPTRWeapon> NewWeapon)
{
	//	TODO :
	// do the same thing no matter your role, except server gets replicated :)
	if (GetOwnerRole() == ROLE_Authority)
	{

	}
	if (GetOwnerRole() == ROLE_AutonomousProxy)
	{

	}
}

void UPTRWeaponComponent::OnWeaponSet_Implementation()
{
	SetWeaponMeshes(FirstPersonWeapon, ThirdPersonWeapon);
}

void UPTRWeaponComponent::SetWeaponStance(const EPTRWeaponStance& NewWeaponStance)
{
	// for now do the same thing no matter your role, but in the future we could diversify
	if (GetOwnerRole() == ROLE_Authority)
	{
		WeaponStance = NewWeaponStance;
	}
	if (GetOwnerRole() == ROLE_AutonomousProxy)
	{
		WeaponStance = NewWeaponStance;
	}
}


void UPTRWeaponComponent::OnFire(EPTRFireMode FireMode)
{
	if (ActiveWeapon)
	{
		if (GetOwnerRole() == ENetRole::ROLE_Authority)
		{
			switch (FireMode)
			{
			case EPTRFireMode::Primary:
				ActiveWeapon->FirePrimary(GetOwner());
				SetWeaponStance(EPTRWeaponStance::Primary);
				break;
			case EPTRFireMode::Secondary:
				ActiveWeapon->FireSecondary(GetOwner());
				SetWeaponStance(EPTRWeaponStance::Secondary);
				break;
			default: ;
			}
		}
		if (GetOwnerRole() == ENetRole::ROLE_AutonomousProxy)
		{
			// Genlty Ask Server
			Net_Fire(FireMode);
			// then simulate :
			switch (FireMode)
			{
			case EPTRFireMode::Primary:
				ActiveWeapon->FirePrimary(GetOwner());
				SetWeaponStance(EPTRWeaponStance::Primary);
				break;
			case EPTRFireMode::Secondary:
				ActiveWeapon->FireSecondary(GetOwner());
				SetWeaponStance(EPTRWeaponStance::Secondary);
				break;
			default: ;
			}
		}
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

void UPTRWeaponComponent::Net_SetWeapon_Implementation(const TSoftObjectPtr<UPTRWeapon>& NewWeapon)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		// todo : check if in inventory, then add to list if not present then switch to it


	}
}

void UPTRWeaponComponent::Net_OnSetWeapon_Implementation(const TSoftObjectPtr<UPTRWeapon>& NewWeapon)
{
	// Update Mesh
	SetWeaponMeshes(FirstPersonWeapon, ThirdPersonWeapon);
}

void UPTRWeaponComponent::Net_SetWeaponStance_Implementation(EPTRWeaponStance NewWeaponStance)
{

	WeaponStance = NewWeaponStance;
}

void UPTRWeaponComponent::OnRep_ActiveWeapon(UPTRWeapon* LastActiveWeapon)
{
	// check if we already have the correct weapon because we're faster than server :P
	if (GetOwnerRole()!= ENetRole::ROLE_Authority)
	{
		if (LastActiveWeapon != ActiveWeapon)
		{
			// Well that sucks; Server changed our weapon for us :///
			// let's update to fix that
			OnWeaponSet();
		}
	}
}

void UPTRWeaponComponent::OnRep_WeaponStance(EPTRWeaponStance LastWeaponStance)
{
	// check if we already have the correct weapon because we're faster than server :P
	if (GetOwnerRole()!= ENetRole::ROLE_Authority)
	{
		if (LastWeaponStance != WeaponStance)
		{
			// Well that sucks; Server changed our weapon for us :///
			// let's update to fix that
			OnWeaponSet();
		}
	}
}

void UPTRWeaponComponent::OnInventoryChange(const FPTRSoftItemPath& Item, int32 ItemCount)
{
	auto SoftItem = FPTRSoftItemPath(Item.ToSoftPath());
	if (auto ItemClass = SoftItem.GetClass())
	{
		if (ItemClass->IsChildOf(UPTRWeapon::StaticClass()))
		{
			AddWeapon(TSoftObjectPtr<UPTRWeapon>(SoftItem.ToSoftPath()));
		}
	}
}


UPTRInventoryComponent* UPTRWeaponComponent::GetInventoryComponent() const
{
	return IPTRInventoryInterface::Execute_GetInventoryComponent(GetOwner());
}


void UPTRWeaponComponent::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME( UPTRWeaponComponent, WeaponStance );
}
