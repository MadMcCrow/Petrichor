// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.


#include "Weapons/PTRWeaponComponent.h"

#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Items/PTRInventoryComponent.h"
#include "Items/PTRInventoryInterface.h"
#include "Net/UnrealNetwork.h"


UPTRWeaponComponent::UPTRWeaponComponent() : Super()
{
	PrimaryComponentTick.bCanEverTick = false;
	PreviousWeapon = nullptr;
}

void UPTRWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	SetIsReplicated(true);
	if (const auto Inv = GetInventoryComponent())
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
	ThirdPersonWeapon = TPSWeapon;
	FirstPersonWeapon = FPSWeapon;


	if (GetWeapon())
	{
		USkeletalMesh* WeaponMesh = nullptr;
		WeaponMesh = GetWeapon()->GetMesh().Get();

		if (FirstPersonWeapon)
		{
			FirstPersonWeapon->SetSkeletalMesh(WeaponMesh, true);
		}
		if (ThirdPersonWeapon)
		{
			ThirdPersonWeapon->SetSkeletalMesh(WeaponMesh, true);
			// update master pose component
			if (FirstPersonWeapon)
			{
				ThirdPersonWeapon->SetMasterPoseComponent(FirstPersonWeapon, true);
			}
		}
	}
}

void UPTRWeaponComponent::SetWeapon(TSoftObjectPtr<UPTRWeapon> NewWeapon)
{
	// Server :
	if (GetOwnerRole() == ROLE_Authority)
	{
		Net_SetWeapon_Implementation(NewWeapon);
	}

	// we're not server but we're gonna do it for ourselves
	if (GetOwnerRole() == ROLE_AutonomousProxy)
	{
		// ask server to do this
		Net_SetWeapon(NewWeapon);

		// in the meantime we shall do it ourselves
		{
			// this will trigger on Rep
			ActiveWeapon = NewWeapon.Get();
			Net_OnSetWeapon_Implementation(); // we know this will be called, better do it now
		}
	}
}

void UPTRWeaponComponent::AddWeapon(TSoftObjectPtr<UPTRWeapon> NewWeapon)
{
	//	TODO : add priority and stuff
	// for now, only set weapon
	SetWeapon(NewWeapon);
}

void UPTRWeaponComponent::OnWeaponSet_Implementation()
{
	// load mesh and set weapon mesh when loaded
	if (ActiveWeapon)
	{
		FStreamableManager& Streamable = UAssetManager::Get().GetStreamableManager();
		FStreamableDelegate StreamDel;
		StreamDel.BindWeakLambda(this, [this]() {SetWeaponMeshes(FirstPersonWeapon, ThirdPersonWeapon);});
		Streamable.RequestAsyncLoad(ActiveWeapon->GetMesh().ToSoftObjectPath(), StreamDel);
	}
}

void UPTRWeaponComponent::SetWeaponStance(const EPTRWeaponStance& NewWeaponStance)
{
	// for now do the same thing no matter your role, but in the future we could diversify
	WeaponStance = NewWeaponStance;
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
	ensureMsgf(GetOwnerRole() == ROLE_Authority, TEXT("Net_SetWeapon_Implementation: this must run on server"));

	// check this is in inventory
	if (!GetInventoryComponent()->HasItem(FPTRSoftItemPath(NewWeapon)) || NewWeapon.IsNull())
	{
		return;
	}
	// this will trigger on Rep
	ActiveWeapon = NewWeapon.LoadSynchronous(); // we need to load item : will this work over network ?
	Net_OnSetWeapon(); // multicast to other players
}

void UPTRWeaponComponent::Net_OnSetWeapon_Implementation()
{
	if (PreviousWeapon != ActiveWeapon)
	{
		SetWeaponMeshes(FirstPersonWeapon, ThirdPersonWeapon); 	// Update Mesh
		Net_SetWeaponStance(EPTRWeaponStance::Idle);
		OnWeaponSet();
	}
	PreviousWeapon = ActiveWeapon;
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
	const auto SoftItem = FPTRSoftItemPath(Item.ToSoftPath());
	const auto ItemClass = SoftItem.GetClass();
	if (ItemClass)
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
