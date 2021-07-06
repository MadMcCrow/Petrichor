// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "PTRCharacterBase.h"
#include "PTRCharacter.generated.h"


class UPTRWeaponComponent;
class UPTRWeapon;
class USkeletalMeshComponent;


UCLASS(Abstract, Blueprintable, config=Game)
class APTRCharacter : public APTRCharacterBase
{
	GENERATED_BODY()
public:

	APTRCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void OnConstruction(const FTransform& Transform) override;

	/**
	 *	Add a weapon to our character
	 *	@param WeaponClass	The weapon to use for this one
	 *	@param bEquip		Wether we shall call EquipWeapon right after adding it
	 *	@todo: Make this networked
	 */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	virtual UPTRWeaponComponent* AddWeapon(TSubclassOf<UPTRWeapon> WeaponClass, bool bEquip = true);

	/**
	*	Equip a weapon making it the one currently used
	*	@param WeaponClass	The weapon to use for this one
	*/
	UFUNCTION(BlueprintCallable, Category="Weapon")
	virtual void EquipWeapon(TSubclassOf<UPTRWeapon> WeaponClass);

	/**
	*	Equip a weapon making it the one currently used - by index in the array
	*	@param Weapon	The weapon to use for this one
	*/
	UFUNCTION(BlueprintCallable, Category="Weapon")
	virtual void EquipWeaponIndex(int32 Weapon);

	/**
	*	@return Currenlty equiped weapon or nullptr if nothing found
	*/
	UFUNCTION(BlueprintPure, Category="Weapon")
	UPTRWeaponComponent* GetEquipedWeapon() const;


protected:

	/**
	 *	Name of the socket for Weapon mesh both on First and third person meshes
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName WeaponSocketName;

	/**
	*	Class of WeaponComponent to spawn
	*	default to UPTRWeaponComponent::StaticClass()
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<UPTRWeaponComponent> WeaponComponentClass;

private:

	/**
	 *	Weapon component will handle firing etc...
	 *	There's one per weapon we have on us
	 */
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TMap<int32,UPTRWeaponComponent*> Weapons;

	/**
	 *	Index of currently active WeaponComponent
	 */
	UPROPERTY(Transient,Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	int32 ActiveWeaponIndex;

	/**
	 *	Weapon Mesh for 1st person view
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstPersonWeaponMeshComponent;

	/**
	*	Weapon Mesh for 3rd person view
	*/
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* ThirdPersonWeaponMeshComponent;

public:

	static FName WeaponComponentBaseName;
	static FName FirstPersonWeaponMeshName;
	static FName ThirdPersonWeaponMeshName;

};