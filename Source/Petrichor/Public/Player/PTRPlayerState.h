// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PTRPlayerState.generated.h"

/**
 *	Player State stores Player information. this is transferred between maps.
 */
UCLASS(ClassGroup=(PTR), Category="Petrichor")
class PETRICHOR_API APTRPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	// CTR
	APTRPlayerState( const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());

	// AActor API
	virtual void BeginPlay() override;
	// \AActor API

protected:

	/**
	 * A datatable of items to give to the player at start
	 * @todo we need a way to know if we need this or the data in the save
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Inventory")
	TSoftObjectPtr<class UDataTable> StartingItem;

private:

	/**
	 *	Inventory component for this player, stores ammunition, various pickups and whats not
	 *	@todo Save system
	 */
	UPROPERTY(Transient, DuplicateTransient, BlueprintReadOnly, meta=(AllowPrivateAccess))
	class UPTRInventoryComponent* PlayerInventory;


public:

	// default name for override in child classes
	static FName InventoryComponentName;

	FORCEINLINE class UPTRInventoryComponent* GetInventoryComponent() const {return PlayerInventory;}


};