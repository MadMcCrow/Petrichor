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
	*	@fn GetPTRCharacter
	*	Get Player's character
	*/
	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category="Petrichor", DisplayName="GetPetrichorPlayerState")
	class APTRPlayerState* GetPTRPlayerState() const;

protected:

	// UUserWidget API
	virtual void NativeConstruct() override;
	// \UUserWidget API

private:

};