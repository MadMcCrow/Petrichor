// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "PTRCharacterBase.h"
#include "PTRCharacter.generated.h"


class UPTRWeaponComponent;
class UPTRWeapon;


UCLASS(Abstract, Blueprintable, config=Game)
class APTRCharacter : public APTRCharacterBase
{
	GENERATED_BODY()
public:

	APTRCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void AddWeapon(TSubclassOf<UPTRWeapon> Weapon);

private:

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UPTRWeaponComponent* WeaponComponent;

public:

	static FName WeaponComponentName;
	FORCEINLINE UPTRWeaponComponent* GetWeaponComponent() const {return WeaponComponent; }

};