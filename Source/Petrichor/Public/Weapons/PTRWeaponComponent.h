// Copyright © Noé Perard-Gayot 2021.

#pragma once


#include "Components/ActorComponent.h"

#include "Petrichor.h"
#include "PTRWeapon.h"
#include "PTRWeaponComponent.generated.h"



class USkeletalMeshComponent;


UCLASS( ClassGroup=(PTR), Within="PTRCharacter" )
class PETRICHOR_API UPTRWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPTRWeaponComponent();

	virtual void InitializeComponent() override;


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

	UFUNCTION(BlueprintCallable, Category= "Weapon")
	class UPTRWeapon* GetWeapon();


	UFUNCTION(BlueprintPure, Category = "Weapon")
	EPTRWeaponStance GetCurrentWeaponStance() const {return WeaponStance;}

	UFUNCTION(BlueprintPure, Category = "Weapon")
	bool IsWeaponDrawn();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetWeaponMeshes(USkeletalMeshComponent* FPSWeapon, USkeletalMeshComponent* TPSWeapon);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetWeapon(TSoftObjectPtr<UPTRWeapon> NewWeapon);

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
	void Net_SetWeapon(const TSoftObjectPtr<UPTRWeapon>& NewWeapon);
	void Net_SetWeapon_Implementation(const TSoftObjectPtr<UPTRWeapon>& NewWeapon);
	bool Net_SetWeapon_Validate(const TSoftObjectPtr<UPTRWeapon>& NewWeapon)	{return true;}

	UFUNCTION()
	void OnRep_Weapon();

private:

	UPROPERTY(Transient, DuplicateTransient, Replicated)
	EPTRWeaponStance WeaponStance;

	UPROPERTY(Transient, DuplicateTransient, ReplicatedUsing = OnRep_Weapon)
	TSoftObjectPtr<UPTRWeapon> WeaponItem;

	/** Only makes sens for owner */
	UPROPERTY(Transient, DuplicateTransient)
	USkeletalMeshComponent* FirstPersonWeapon;

	/** Only makes sens for TPS view */
	UPROPERTY(Transient, DuplicateTransient)
	USkeletalMeshComponent* ThirdPersonWeapon;


public:

	FORCEINLINE TMap<EPTRCharacterViewType, USkeletalMeshComponent*> GetWeaponMeshes() const {return {{EPTRCharacterViewType::FirstPerson, FirstPersonWeapon}, {EPTRCharacterViewType::ThirdPerson,ThirdPersonWeapon}};}

	FORCEINLINE FSoftObjectPath GetWeapon() const {return WeaponItem.ToSoftObjectPath();}
};