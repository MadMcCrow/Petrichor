// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#include "Characters/PTRCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Player/PTRPlayerState.h"
#include "Weapons/PTRWeaponComponent.h"

FName APTRCharacter::WeaponComponentName		= TEXT("WeaponComponent");
FName APTRCharacter::FirstPersonWeaponMeshName	= TEXT("WeaponFPSMeshComp");
FName APTRCharacter::ThirdPersonWeaponMeshName	= TEXT("WeaponTPSMeshComp");

APTRCharacter::APTRCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
    ,WeaponSocketName("Weapon")
{
	// WeaponMeshes
	// FP
	FirstPersonWeaponMeshComponent = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, FirstPersonWeaponMeshName);
	FirstPersonWeaponMeshComponent->SetupAttachment(GetFirstPersonMesh(), WeaponSocketName);
	FirstPersonWeaponMeshComponent->SetOnlyOwnerSee(true);
	// TP
	ThirdPersonWeaponMeshComponent = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, ThirdPersonWeaponMeshName);
	ThirdPersonWeaponMeshComponent->SetupAttachment(GetThirdPersonMesh(), WeaponSocketName);
	ThirdPersonWeaponMeshComponent->SetOnlyOwnerSee(false);
	ThirdPersonWeaponMeshComponent->SetOwnerNoSee(true);

	WeaponComponent = ObjectInitializer.CreateDefaultSubobject<UPTRWeaponComponent>(this, WeaponComponentName);
	WeaponComponent->SetIsReplicated(true);
	WeaponComponent->SetWeaponMeshes(FirstPersonWeaponMeshComponent,ThirdPersonWeaponMeshComponent);
}

void APTRCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	ThirdPersonWeaponMeshComponent->SetSkeletalMesh(FirstPersonWeaponMeshComponent->SkeletalMesh);
	ThirdPersonWeaponMeshComponent->SetMasterPoseComponent(FirstPersonWeaponMeshComponent);
}

void APTRCharacter::PossessedBy(AController* NewController)
{
	// this function is Server only
	Super::PossessedBy(NewController);

}

void APTRCharacter::OnRep_PlayerState()
{
	// this function is Client only
	Super::OnRep_PlayerState();

}

UPTRInventoryComponent* APTRCharacter::GetInventoryComponent_Implementation() const
{
	if (const APTRPlayerState* PS = GetPlayerState<APTRPlayerState>())
	{
		return Execute_GetInventoryComponent(PS);
	}

	// return nullptr... for now
	return nullptr;
}


void APTRCharacter::AddWeapon(TSoftObjectPtr<UPTRWeapon> Weapon, bool bEquip)
{
	if (WeaponComponent)
	{
		WeaponComponent->SetWeaponMeshes(FirstPersonWeaponMeshComponent, ThirdPersonWeaponMeshComponent);
		WeaponComponent->SetWeapon(Weapon);
	}
}

void APTRCharacter::EquipWeapon(TSoftObjectPtr<UPTRWeapon> Weapon)
{
	/*
	for (auto WeaponItr:Weapons)
	{
		if (WeaponItr.Value->GetWeapon() == Weapon)
		{
			EquipWeaponIndex(WeaponItr.Key);
		}
	}
	*/
}

void APTRCharacter::EquipWeaponIndex(int32 Weapon)
{
	ActiveWeaponIndex = Weapon;
	// do extra stuff here ?
}


void APTRCharacter::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME( APTRCharacter, ActiveWeaponIndex );
}
