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


	UFUNCTION(BlueprintPure, Category = "Weapon")
	EPTRWeaponStance GetCurrentWeaponStance() const {return WeaponStance;}

	UFUNCTION(BlueprintPure, Category = "Weapon")
	bool IsWeaponDrawn();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetWeaponMeshes(USkeletalMeshComponent* FPSWeapon, USkeletalMeshComponent* TPSWeapon);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetWeapon(TSubclassOf<UPTRWeapon> NewWeaponClass);

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

	/** For now we use CDO as weapon to use */
	UPROPERTY(Transient)
	class UPTRWeapon* WeaponCDO;

	/** Only makes sens for owner */
	UPROPERTY(Transient, DuplicateTransient)
	USkeletalMeshComponent* FirstPersonWeapon;

	/** Only makes sens for TPS view */
	UPROPERTY(Transient, DuplicateTransient)
	USkeletalMeshComponent* ThirdPersonWeapon;


public:

	FORCEINLINE TMap<EPTRCharacterViewType, USkeletalMeshComponent*> GetWeaponMeshes() const {return {{EPTRCharacterViewType::FirstPerson, FirstPersonWeapon}, {EPTRCharacterViewType::ThirdPerson,ThirdPersonWeapon}};}
	FORCEINLINE UPTRWeapon* GetWeapon() const {return UPTRWeapon::GetWeaponObject(this, WeaponClass);}
	FORCEINLINE TSubclassOf<UPTRWeapon> GetWeaponClass() const {return WeaponClass;}
};