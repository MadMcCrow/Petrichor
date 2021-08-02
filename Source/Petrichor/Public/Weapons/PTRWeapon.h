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
UCLASS(ClassGroup=(PTR), Category ="Weapon")
class PETRICHOR_API UPTRWeapon : public UPTRItem
{
	GENERATED_BODY()

protected:

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
	 *	The mesh to use, both in FP and TP views
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


	/** Game Event triggered on Primary Fire */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "GameEvent")
	class UPTRGameEvent* PrimaryGameEvent;

	/** Game Event triggered on Secondary Fire */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "GameEvent")
	class UPTRGameEvent* SecondaryGameEvent;


public:

	/** Custom event called when firing Weapon */
	UFUNCTION(BlueprintNativeEvent, Category= "Weapon" )
	void FirePrimary(AActor * Instigator);
	virtual void FirePrimary_Implementation(AActor * Instigator);

	/** Custom event called when firing Weapon */
	UFUNCTION(BlueprintNativeEvent, Category= "Weapon")
	void FireSecondary(AActor * Instigator);
	virtual void FireSecondary_Implementation(AActor * Instigator);

	/** Helper to get animation faster for the FPV and TPV characters */
	UFUNCTION(BlueprintPure, Category = "Weapon|Animations")
	TSoftObjectPtr<UAnimSequenceBase> GetAnimationAsset(EPTRCharacterViewType View, EPTRWeaponStance Stance) const;

	/** Helper to get animation faster  for the weapon itself */
	UFUNCTION(BlueprintPure, Category = "Weapon|Animations")
	TSoftObjectPtr<UAnimSequenceBase> GetMeshAnimation(EPTRWeaponStance Stance) const;

	/** Simple getters with const reference */
	FORCEINLINE const TSoftObjectPtr<USkeletalMesh>& GetMesh() const {return WeaponMesh;}
	FORCEINLINE const TMap<EPTRWeaponStance, TSoftObjectPtr<UAnimSequenceBase>>& GetFirstPersonCharacterAnimations() const {return PlayerAnimations;}
	FORCEINLINE const TMap<EPTRWeaponStance, TSoftObjectPtr<UAnimSequenceBase>>& GetThirdPersonCharacterAnimations() const {return CharacterAnimations;}

};
