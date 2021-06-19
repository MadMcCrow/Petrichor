// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Weapons/PTRWeaponTypes.h"

#include "PTRCharacterAnimInstance.generated.h"

/** What type of animation Instance is it ? */
UENUM(BlueprintType)
enum class EPTRCharacterAnimInstanceType : uint8
{
	FirstPerson		UMETA(DisplayName="FirstPerson Arms"),
	ThirdPerson		UMETA(DisplayName="Whole Body Animations")
};


/**
 *
 */
UCLASS()
class PETRICHOR_API UPTRCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPTRCharacterAnimInstance(const FObjectInitializer& Initializer);

	virtual void NativeInitializeAnimation() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	EPTRCharacterAnimInstanceType CharacterType;

public:

	UFUNCTION(BlueprintPure, Category="Animation|Locomotion")
	bool bIsCrouched() const;

	UFUNCTION(BlueprintPure, Category="Animation|Weapon")
	UAnimSequenceBase* GetWeaponAnimation() const;


protected:

	UFUNCTION()
	virtual void LoadWeaponAnimations();

private:

	UFUNCTION()
	void OnWeaponAnimationsLoaded();

	UPROPERTY(Transient)
	class APTRCharacter* OwningCharacter;

	// Only requiered for async load
	UPROPERTY()
	TMap<EPTRWeaponStance, TSoftObjectPtr<UAnimSequenceBase>> WeaponSequenceAssets;

	// The loaded Sequences
	UPROPERTY()
	TMap<EPTRWeaponStance, UAnimSequenceBase*> WeaponSequences;



};