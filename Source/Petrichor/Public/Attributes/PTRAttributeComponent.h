// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Items/PTRInventoryComponent.h"

#include "PTRAttributeComponent.generated.h"

/**
 *	Advanced struct for holding items base values
 */
USTRUCT(BlueprintType, Category="Petrichor|Attributes")
struct FPTRAttributeDefinition : public FTableRowBase
{
	GENERATED_BODY()

	// conversion CTR for ease of use
	FPTRAttributeDefinition(const FPTRSoftItemPath& AssetPath = FPTRSoftItemPath()) : Asset(AssetPath.ToSoftPath())
	{}

	/**
	 *	Unique ID of that Item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowedClasses="PTRItem"))
	FSoftObjectPath Asset;

	/**
	 *	Amount stored
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BaseValue;

	// hash for Set and maps
	FORCEINLINE friend uint32 GetTypeHash(const FPTRAttributeDefinition& Key)
	{
		// basically only check for AssetID
		return GetTypeHash(Key.Asset);
	}

	// equal operator for comparisons
	bool operator==(const FPTRAttributeDefinition& Other) const
	{
		const uint32 A = GetTypeHash(*this);
		const uint32 B = GetTypeHash(Other);
		return A == B;
	}



};

/**
*	Pair of values for attributes
*/
USTRUCT(BlueprintType, Category="Petrichor|Attributes")
struct FPTRAttribute
{
	GENERATED_BODY()

	/**
	 *	Amount stored
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BaseValue;

	/**
	*	Amount stored
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentValue;

	//CTR
	FPTRAttribute(int32 InCurrentValue = 0, int32 InBaseValue = 0)
	: BaseValue(InBaseValue), CurrentValue(InCurrentValue)
	{}

};



/**
 *  UPTRAttributeComponent
 *  @brief	Allows interpretation of items as attributes
 *  @note	this will help to have life, ammunition.
 *  @todo	it also triggers events when attribute reaches 0/100%
 */
UCLASS(ClassGroup=(PTR), config=Game, Category="Petrichor|Items")
class UPTRAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Default CTR
	UPTRAttributeComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**
	 * Init the attribute set
	 * @param InAttributes	List of attributes, usually from datatable
	 * @note should be called from server
	 */
	UFUNCTION()
	void InitAttributes(const TArray<FPTRAttributeDefinition> InAttributes);

	/**
	 *	GetAttribute
	 *	Function to get base and count at the same place
	 */
	UFUNCTION(BlueprintPure, Category= "Attribute")
	FPTRAttribute GetAttribute(const FPTRSoftItemPath& InItem) const;

	/**
	 *	GetAttributeBaseValue
	 *	Function to get base value only
	 */
	UFUNCTION(BlueprintPure, Category= "Attribute")
	int32 GetAttributeBaseValue(const FPTRSoftItemPath& InItem) const;

	/**
	 *	GetAttributeBaseValue
	 *	Function to get base value only
	 */
	UFUNCTION(BlueprintPure, Category= "Attribute")
	int32 GetAttributeCount(const FPTRSoftItemPath& InItem) const;


	/**
	*  InventoryComponent
	*   the inventory component we're watching
	*/
	UFUNCTION(BlueprintPure, Category= "Attribute")
	UPTRInventoryComponent* GetInventoryComponent() const;

private:

	/**
	 *  The items this inventory has
	 *  FPTRInventoryItem provide a hash function to ensure that there's no double
	 *  TSet ensure faster searches compared to arrays.
	 */
	UPROPERTY(Transient, VisibleAnywhere, Category="Attributes")
	TSet<FPTRAttributeDefinition> Attributes;

	/**
	 *  InventoryComponent
	 *   the inventory component we're watching
	 */
	UPROPERTY(Transient, DuplicateTransient)
	const UPTRInventoryComponent * InventoryComponent;




};
