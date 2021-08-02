// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "PTRCharacterBase.h"
#include "Items/PTRInventoryComponent.h"
#include "Items/PTRInventoryInterface.h"

#include "PTRCharacter.generated.h"


class UPTRWeaponComponent;
class UPTRWeapon;
class USkeletalMeshComponent;


UCLASS(Abstract, Blueprintable, config=Game)
class APTRCharacter : public APTRCharacterBase, public IPTRInventoryInterface
{
	GENERATED_BODY()
public:

	APTRCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// APawn API
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	// \APawn API

	// IPTRInventoryInterface API
	virtual class UPTRInventoryComponent* GetInventoryComponent_Implementation() const override;
	// \IPTRInventoryInterface API

	/**
	 *	Add a weapon to our character
	 *	@param WeaponClass	The weapon to use for this one
	 *	@param bEquip		Wether we shall call EquipWeapon right after adding it
	 *	@todo: Make this networked
	 */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	virtual void AddWeapon(TSoftObjectPtr<UPTRWeapon> Weapon, bool bEquip = true);

	/**
	*	Equip a weapon making it the one currently used
	*	@param WeaponClass	The weapon to use for this one
	*/
	UFUNCTION(BlueprintCallable, Category="Weapon")
	virtual void EquipWeapon(TSoftObjectPtr<UPTRWeapon> Weapon);

	/**
	*	Equip a weapon making it the one currently used - by index in the array
	*	@param Weapon	The weapon to use for this one
	*/
	UFUNCTION(BlueprintCallable, Category="Weapon")
	virtual void EquipWeaponIndex(int32 Weapon);


protected:

	/**
	 *	Name of the socket for Weapon mesh both on First and third person meshes
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName WeaponSocketName;

private:

	/**
	 *	Weapon component will handle firing etc...
	 */
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	class UPTRWeaponComponent* WeaponComponent;

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

	static FName WeaponComponentName;
	static FName FirstPersonWeaponMeshName;
	static FName ThirdPersonWeaponMeshName;


	FORCEINLINE UPTRWeaponComponent* GetWeaponComponent() const {return WeaponComponent;}

};
