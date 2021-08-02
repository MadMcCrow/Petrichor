// Copyright © Noé Perard-Gayot 2021.

#pragma once


#include "Components/ActorComponent.h"

#include "Petrichor.h"
#include "PTRWeapon.h"
#include "Items/PTRInventoryComponent.h"

#include "PTRWeaponComponent.generated.h"



class USkeletalMeshComponent;

/**
 *	Component responsible for handling weapons
 */
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
	void SetWeapon(TSoftObjectPtr<UPTRWeapon> NewWeapon);

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
	void OnWeaponSet();
	virtual void OnWeaponSet_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetWeaponStance(const EPTRWeaponStance& NewWeaponStance);

protected:

	virtual void OnFire(EPTRFireMode FireMode);

	UFUNCTION(Server, Reliable, WithValidation)
	void Net_Fire(EPTRFireMode FireMode);
	void Net_Fire_Implementation(EPTRFireMode FireMode);
	bool Net_Fire_Validate(EPTRFireMode FireMode)	{return true;}

	UFUNCTION(Server, Reliable, WithValidation)
	void Net_SetWeapon(const TSoftObjectPtr<UPTRWeapon>& NewWeapon);
	void Net_SetWeapon_Implementation(const TSoftObjectPtr<UPTRWeapon>& NewWeapon);
	bool Net_SetWeapon_Validate(const TSoftObjectPtr<UPTRWeapon>& NewWeapon)	{return true;}

	/**
	 *	Update what we should change when weapon change
	 */
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Net_OnSetWeapon(const TSoftObjectPtr<UPTRWeapon>& NewWeapon);
	void Net_OnSetWeapon_Implementation(const TSoftObjectPtr<UPTRWeapon>& NewWeapon);
	bool Net_OnSetWeapon_Validate(const TSoftObjectPtr<UPTRWeapon>& NewWeapon)	{return true;}

	/**
	 *	Update how weapon animation should behave, this is to message the server about our change.
	 */
	UFUNCTION(Server, Reliable, WithValidation)
	void Net_SetWeaponStance(EPTRWeaponStance NewWeaponStance);
	void Net_SetWeaponStance_Implementation(EPTRWeaponStance NewWeaponStance);
	bool Net_SetWeaponStance_Validate(EPTRWeaponStance NewWeaponStance)	{return true;}



private:


	UPROPERTY(Transient, DuplicateTransient)
	TSet<TSoftObjectPtr<UPTRWeapon>> WeaponItems;

	/** Only makes sens for owner */
	UPROPERTY(Transient, DuplicateTransient)
	USkeletalMeshComponent* FirstPersonWeapon;

	/** Only makes sens for TPS view */
	UPROPERTY(Transient, DuplicateTransient)
	USkeletalMeshComponent* ThirdPersonWeapon;

	/**Currently active weapon */
	UPROPERTY(Transient, DuplicateTransient, ReplicatedUsing="OnRep_ActiveWeapon")
	UPTRWeapon* ActiveWeapon;

	/** Weapon animation stance */
	UPROPERTY(Transient, DuplicateTransient, ReplicatedUsing="OnRep_WeaponStance")
	EPTRWeaponStance WeaponStance;

	UFUNCTION()
	void OnRep_ActiveWeapon(UPTRWeapon* LastActiveWeapon);

	UFUNCTION()
	void OnRep_WeaponStance(EPTRWeaponStance LastWeaponStance);


public:

	// for quick access
	UPTRInventoryComponent* GetInventoryComponent() const;

	FORCEINLINE TMap<EPTRCharacterViewType, USkeletalMeshComponent*> GetWeaponMeshes() const {return {{EPTRCharacterViewType::FirstPerson, FirstPersonWeapon}, {EPTRCharacterViewType::ThirdPerson,ThirdPersonWeapon}};}
	FORCEINLINE UPTRWeapon* GetWeapon() const {return ActiveWeapon;}
};
