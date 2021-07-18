// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "PTRPlayerState.generated.h"

/**
 *	Player State stores Player information. this is transferred between maps.
 */
UCLASS(ClassGroup=(PTR), Category="Petrichor")
class PETRICHOR_API APTRPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	// CTR
	APTRPlayerState( const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());

	// IAbilitySystemInterface API
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// \IAbilitySystemInterface API

private:

	/**
	 *	Inventory component for this player, stores ammunition, various pickups and whats not
	 */
	UPROPERTY(Transient)
	class UPTRInventoryComponent* PlayerInventory;

	/**
	*	Inventory component for this player, stores ammunition, various pickups and whats not
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameplayAbilitySystem", meta=(AllowPrivateAccess="true"))
	class UPTRAbilitySystemComponent * AbilitySystemComponent;

	/** the Player attribute set */
	UPROPERTY()
	class UPTRHealthArmorAttributeSet* CharacterAttributeSet;


public:

	/** Simple inline getter for component */
	FORCEINLINE UPTRInventoryComponent* GetPlayerInventoryComponent() const { return PlayerInventory;}

	/** Simple inline getter for component */
	FORCEINLINE class UPTRHealthArmorAttributeSet* GetCharacterAttributeSet() const {return CharacterAttributeSet;}

	// default name for override in child classes
	static FName InventoryComponentName;

	// default name for override in child classes
	static FName GASComponentName;

};