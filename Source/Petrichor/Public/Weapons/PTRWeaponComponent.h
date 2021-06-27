// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "PTRWeapon.h"
#include "PTRWeaponTypes.h"
#include "PTRWeaponComponent.generated.h"




UCLASS( ClassGroup=(PTR), Within="PTRCharacter" )
class PETRICHOR_API UPTRWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPTRWeaponComponent();

	virtual void InitializeComponent() override;

	UPTRWeapon* GetWeapon() const;

	/**
	 *	@fn HolsterWeapon
	 *	Put weapon in holster, to undo , @see DrawWeapon
	 */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void HolsterWeapon();

	/**
	*	@fn DrawWeapon
	*	Readies weapon, to undo , @see HolsterWeapon
	*/
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void DrawWeapon();

	/**
	*	@fn AimWeapon
	*	Put weapon in ironsight, to undo , @see DrawWeapon
	*/
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void FirePrimary();

	/**
	*	@fn DrawWeapon
	*	Readies weapon, to undo , @see HolsterWeapon
	*/
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void FireSecondary();


	UFUNCTION(BlueprintPure, Category = "Weapon")
	EPTRWeaponStance GetCurrentWeaponStance() const {return WeaponStance;}

	UFUNCTION(BlueprintPure, Category = "Weapon")
	bool IsWeaponDrawn();

protected:


	virtual void OnFire(EPTRFireMode FireMode);

	UFUNCTION(Server, Reliable, WithValidation)
	void Net_Fire(EPTRFireMode FireMode);
	void Net_Fire_Implementation(EPTRFireMode FireMode);
	bool Net_Fire_Validate(EPTRFireMode FireMode)	{return true;}

	UFUNCTION(Server, Reliable, WithValidation)
	void Net_UpdateWeaponStance(EPTRWeaponStance NewWeaponStance);
	void Net_UpdateWeaponStance_Implementation(EPTRWeaponStance NewWeaponStance);
	bool Net_UpdateWeaponStance_Validate(EPTRWeaponStance NewWeaponStance)	{return true;}


	UFUNCTION(Server, Reliable, WithValidation)
	void Net_SetWeapon(TSubclassOf<UPTRWeapon> NewWeaponClass);
	void Net_SetWeapon_Implementation(TSubclassOf<UPTRWeapon> NewWeaponClass);
	bool Net_SetWeapon_Validate(TSubclassOf<UPTRWeapon> NewWeaponClass)	{return true;}

	UFUNCTION()
	void OnRep_WeaponClass();

private:

	UPROPERTY(Transient, DuplicateTransient, Replicated)
	EPTRWeaponStance WeaponStance;

	UPROPERTY(Transient, DuplicateTransient, ReplicatedUsing = OnRep_WeaponClass)
	TSubclassOf<UPTRWeapon> WeaponClass;

	UPROPERTY(Transient)
	class UPTRWeapon* WeaponCDO;
};