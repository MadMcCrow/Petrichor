// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "PTRWeaponTypes.h"
#include "UObject/NoExportTypes.h"

#include "PTRWeapon.generated.h"

// forward declaration
class UPTRAmmunition;

/**
 *	Base Class for weapons
 */
UCLASS(Abstract, Category ="Weapon")
class PETRICHOR_API UPTRWeapon : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh|Animations")
	TMap<EPTRWeaponStance, TSoftObjectPtr<UAnimSequenceBase>> CharacterAnimations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh|Animations")
	TMap<EPTRWeaponStance, TSoftObjectPtr<UAnimSequenceBase>> WeaponAnimations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TSoftObjectPtr<USkeletalMesh> WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo", Instanced)
	UPTRAmmunition* Ammunition;

protected:

	UFUNCTION(BlueprintNativeEvent, Category= "Weapon" )
	void FirePrimary();
	void FirePrimary_Implementation() {NativeFirePrimary();}

	UFUNCTION(BlueprintNativeEvent, Category= "Weapon")
	void FireSecondary();
	void FireSecondary_Implementation() {NativeFirePrimary();}

protected:
	UFUNCTION()
	virtual void NativeFirePrimary() {};

	UFUNCTION()
	virtual void NativeFireSecondary() {};
};