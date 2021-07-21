// Copyright © Noé Perard-Gayot 2021.

#include "Characters/PTRCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Player/PTRPlayerState.h"
#include "Weapons/PTRWeaponComponent.h"

FName APTRCharacter::WeaponComponentBaseName	= TEXT("WeaponComponent");
FName APTRCharacter::FirstPersonWeaponMeshName	= TEXT("WeaponFPSMeshComp");
FName APTRCharacter::ThirdPersonWeaponMeshName	= TEXT("WeaponTPSMeshComp");

APTRCharacter::APTRCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
    ,WeaponSocketName("Weapon")
    ,WeaponComponentClass(UPTRWeaponComponent::StaticClass())
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

UPTRInventoryComponent* APTRCharacter::GetInventory() const
{
	if (const APTRPlayerState* PS = GetPlayerState<APTRPlayerState>())
	{
		return PS->GetInventoryComponent();
	}

	// return nullptr... for now
	return nullptr;
}

UPTRWeaponComponent* APTRCharacter::AddWeapon(TSubclassOf<UPTRWeapon> WeaponClass, bool bEquip)
{
	if (WeaponClass == nullptr)
	{
		return nullptr;
	}

	const UPTRWeapon* Weapon = UPTRWeapon::GetWeaponObject(this, WeaponClass);
	const FString NameStr = WeaponComponentBaseName.ToString() + FString::Printf(TEXT("%d"), Weapon->WantedIndex);
	auto WeaponComp = NewObject<UPTRWeaponComponent>(this, WeaponComponentClass, MakeUniqueObjectName(this, WeaponClass,FName(*NameStr)));

	if (WeaponComp)
	{
		WeaponComp->SetWeaponMeshes(FirstPersonWeaponMeshComponent, ThirdPersonWeaponMeshComponent);
		WeaponComp->SetWeapon(WeaponClass);
		WeaponComp->RegisterComponent();
		WeaponComp->SetIsReplicated(true);
		// Todo : add safety for already present weapon at index :
		Weapons.Add(Weapon->WantedIndex, WeaponComp);
		return WeaponComp;
	}

	return nullptr;
}

void APTRCharacter::EquipWeapon(TSubclassOf<UPTRWeapon> WeaponClass)
{
	for (auto WeaponItr:Weapons)
	{
		if (WeaponItr.Value->GetWeaponClass() == WeaponClass)
		{
			EquipWeaponIndex(WeaponItr.Key);
		}
	}
}

void APTRCharacter::EquipWeaponIndex(int32 Weapon)
{
	ActiveWeaponIndex = Weapon;
	// do extra stuff here ?
}

UPTRWeaponComponent* APTRCharacter::GetEquipedWeapon() const
{
	if (UPTRWeaponComponent* const* FoundWeapon = Weapons.Find(ActiveWeaponIndex))
	{
		return *FoundWeapon;
	}
	return nullptr;
}


void APTRCharacter::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME( APTRCharacter, ActiveWeaponIndex );
}