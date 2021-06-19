// Copyright © Noé Perard-Gayot 2021.


#include "Characters/PTRCharacterAnimInstance.h"
#include "Characters/PTRCharacter.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Weapons/PTRWeapon.h"
#include "Weapons/PTRWeaponComponent.h"

UPTRCharacterAnimInstance::UPTRCharacterAnimInstance(const FObjectInitializer& Initializer) : Super(Initializer)
{

}

void UPTRCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (auto Character = Cast<APTRCharacter>(TryGetPawnOwner()))
	{
		OwningCharacter = Character;
	}
}

bool UPTRCharacterAnimInstance::bIsCrouched() const
{
	if (OwningCharacter && OwningCharacter->GetMovementComponent())
	{
		return OwningCharacter->GetMovementComponent()->IsCrouching();
	}
	return false;
}

UAnimSequenceBase* UPTRCharacterAnimInstance::GetWeaponAnimation() const
{

	if (OwningCharacter)
	{
		if (UPTRWeaponComponent* WeaponComp = OwningCharacter->GetWeaponComponent())
		{
			if (auto Anim = WeaponSequences.Find(WeaponComp->GetCurrentWeaponStance()))
			{
				return *Anim;
			}
		}
	}

	if (auto Anim = WeaponSequences.Find(EPTRWeaponStance::None))
	{
		return *Anim;
	}

	return nullptr;
}

void UPTRCharacterAnimInstance::LoadWeaponAnimations()
{
	if (OwningCharacter)
	{
		if (UPTRWeaponComponent* WeaponComp = OwningCharacter->GetWeaponComponent())
		{
			if(auto Weapon =  WeaponComp->GetWeapon())
			{
				switch (CharacterType)
				{
				case EPTRCharacterAnimInstanceType::FirstPerson:
					WeaponSequenceAssets = Weapon->WeaponAnimations;
					break;
				case EPTRCharacterAnimInstanceType::ThirdPerson:
					WeaponSequenceAssets = Weapon->CharacterAnimations;
					break;
				}

			TArray<FSoftObjectPath> AnimsToLoad;
			for (auto itr: WeaponSequenceAssets)
			{
				auto AnimAsset = itr.Value;
				AnimsToLoad.Add(AnimAsset.ToSoftObjectPath());
			}

			FStreamableManager& Streamable = UAssetManager::Get().GetStreamableManager();
			Streamable.RequestAsyncLoad(AnimsToLoad, FStreamableDelegate::CreateUObject(this, &UPTRCharacterAnimInstance::OnWeaponAnimationsLoaded));
			}
		}
	}
}

void UPTRCharacterAnimInstance::OnWeaponAnimationsLoaded()
{
	WeaponSequences.Empty();
	for (auto itr: WeaponSequenceAssets)
	{
		auto Stance  = itr.Key;
		auto AnimAsset = itr.Value.Get();
		WeaponSequences.Add(Stance, AnimAsset);
	}
}