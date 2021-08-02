// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.


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
		/*
		if (UPTRWeaponComponent* WeaponComp = OwningCharacter->GetWeaponComponent())
		{
			if (auto Anim = WeaponSequences.Find(WeaponComp->GetCurrentWeaponStance()))
			{
				return *Anim;
			}
		}
		*/
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
				case EPTRCharacterViewType::FirstPerson:
					WeaponSequenceAssets = Weapon->GetFirstPersonCharacterAnimations();
					break;
				case EPTRCharacterViewType::ThirdPerson:
					WeaponSequenceAssets = Weapon->GetThirdPersonCharacterAnimations();
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
