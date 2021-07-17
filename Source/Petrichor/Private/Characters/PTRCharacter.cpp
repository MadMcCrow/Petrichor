// Copyright © Noé Perard-Gayot 2021.

#include "Characters/PTRCharacter.h"
#include "GameplayAbilitySystem/PTRAbilitySystemComponent.h"
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
	Super::PossessedBy(NewController);
	// Server only
	if (APTRPlayerState* PS = GetPlayerState<APTRPlayerState>())
	{
		// Set the ASC on the Server. Clients do this in OnRep_PlayerState()
		AbilitySystemComponent = Cast<UPTRAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		// AI won't have PlayerControllers so we can init again here just to be sure. No harm in initing twice for heroes that have PlayerControllers.
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
	}

}

void APTRCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// Client only
	if (APTRPlayerState* PS = GetPlayerState<APTRPlayerState>())
	{
		// Set the ASC for clients. Server does this in PossessedBy.
		AbilitySystemComponent = Cast<UPTRAbilitySystemComponent>(PS->GetAbilitySystemComponent());

		// Init ASC Actor Info for clients. Server will init its ASC when it possesses a new Actor.
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
	}
}

UAbilitySystemComponent* APTRCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
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