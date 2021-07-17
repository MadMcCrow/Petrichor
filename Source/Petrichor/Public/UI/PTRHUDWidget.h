// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "PTRHUDWidget.generated.h"


/**
 *	@class UPTRHUDWidget
 *	@brief A Widget meant to be drawn on the HUD to display
 */
UCLASS(Abstract, ClassGroup=(PTR), Category="Petrichor|HUD")
class UPTRHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/**
	 *	@fn GetPTRCharacter
	 *	Get Player's character
	 */
	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category="Petrichor", DisplayName="GetPetrichorCharacter")
	class APTRCharacter* GetPTRCharacter() const;

	/**
	 *	@fn GetPTRGameplayAbilitySystem
	 *	Get Player's Ability system
	 *	This will get the one referenced in the character.
	 */
	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category="Petrichor", DisplayName="GetPetrichorGameplayAbilitySystem")
	class UPTRAbilitySystemComponent* GetPTRGameplayAbilitySystem() const;

protected:

	// UUserWidget API
	virtual void NativeConstruct() override;
	// \UUserWidget API

private:

};