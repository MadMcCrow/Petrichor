// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "Petrichor.h"
#include "Items/PTRItem.h"
#include "PTRWeapon.generated.h"

// forward declaration
class UPTRAmmunition;

/**
 *	Base Class for weapons
 */
UCLASS(ClassGroup=(PTR), Abstract, Category ="Weapon")
class PETRICHOR_API UPTRWeapon : public UPTRItem
{
	GENERATED_BODY()

public:

	/**
	*	The animation for the 1rst person mesh
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh|Animations")
	TMap<EPTRWeaponStance, TSoftObjectPtr<UAnimSequenceBase>> PlayerAnimations;

	/**
	 *	The animation for the 3rd person mesh
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh|Animations")
	TMap<EPTRWeaponStance, TSoftObjectPtr<UAnimSequenceBase>> CharacterAnimations;

	/**
	 *	The animation for the weapon meshes
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh|Animations")
	TMap<EPTRWeaponStance, TSoftObjectPtr<UAnimSequenceBase>> WeaponAnimations;

	/**
	 *	The mesh to use, bot in FP and TP views
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TSoftObjectPtr<USkeletalMesh> WeaponMesh;

	/**
	 *	The ammunition type to use
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	TSoftObjectPtr<UPTRAmmunition> Ammunition;

	/**
	 *	The index at which we should add this weapon in the player weapon "inventory"
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int32 WantedIndex;

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


public:

	/**
	 *  Will get you a live object of that weapon.
	 */
	UFUNCTION(BlueprintCallable, Category = "Weapon", meta = (WorldContext = "Outer"))
	static UPTRWeapon* GetWeaponObject(const UObject* Outer, TSubclassOf<UPTRWeapon> WeaponClass);
};