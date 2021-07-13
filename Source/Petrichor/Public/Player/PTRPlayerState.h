// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PTRPlayerState.generated.h"

/**
 *	Player State stores Player information. this is transferred between maps.
 */
UCLASS(ClassGroup=(PTR))
class PETRICHOR_API APTRPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	// CTR
	APTRPlayerState( const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());

private:

	/**
	 *	Inventory component for this player, stores ammunition, various pickups and whats not
	 */
	UPROPERTY(Transient)
	class UPTRInventoryComponent* PlayerInventory;

public:

	/** Simple inline getter for component */
	FORCEINLINE UPTRInventoryComponent* GetPlayerInventoryComponent() const { return PlayerInventory;}

	// default name for override in child classes
	static FName InventoryComponentName;
};