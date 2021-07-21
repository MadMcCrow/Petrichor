// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "Subsystems/EngineSubsystem.h"
#include "PTRAttributeSubsystem.generated.h"

// Log category for this subsystem
DECLARE_LOG_CATEGORY_EXTERN(LogAttributeSubsystem, Log, All);

/**
 *	A simple struct to help generate many attributes from project settings
 */
USTRUCT(BlueprintType, Category="PTR|Attribute")
struct FPTRAttributeDefinition
{
	GENERATED_BODY()

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName InternalName;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;

};

/**
*	Attribute System core.
*	Attribute are normally handled by the Item/Inventory system,
*	but they can be created programatically and do not requiere any assets
*	This Subsystem will create and own all the "Dynamic Items" that makes the attributes
*	@todo : maybe replace by asset manager
*/
UCLASS(ClassGroup=(PTR), config=Game, minimalapi, Category="PTR|Attribute")
class UPTRAttributeSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:

	// CTR
	UPTRAttributeSubsystem();

	// UGameInstanceSubsystem API
	virtual void Initialize	(FSubsystemCollectionBase & Collection) override;
	virtual void Deinitialize() override;
	// \UGameInstanceSubsystem API

	/**
	 *	GetAttributeID
	 *	@return The stored Primary Asset ID of the stored DynamicAttribute that correspond to this name or nullptr
	 */
	FPrimaryAssetId GetAttributeID(FName InternalName) const;

	/**
	 *	GetAttributeID
	 *	@return The stored Primary Asset ID of the DynamicAttribute that correspond to this specific class or nullptr
	 */
	FPrimaryAssetId GetAttributeID(UClass* AttributeClass) const;

	/**
	 *	GetAttribute
	 *	@return The Asset Path of the DynamicAttribute that correspond to that correspond to this name or nullptr
	 */
	FSoftObjectPath GetAttribute(FName InternalName) const;

	/**
	*	GetAttribute
	*	@return The Asset Path of the DynamicAttribute that correspond to this specific class or nullptr
	*/
	FSoftObjectPath GetAttribute(UClass* AttributeClass) const;


	/**
	 *	GetAttributeSubsystem
	 *	Simpler singleton-like getter
	 *	@return the Attribute subsystem if it exists
	 */
	UFUNCTION(BlueprintPure, Category = "PTR|Attribute", meta = (WorldContext = "ContextObject"))
	static UPTRAttributeSubsystem* GetAttributeSubsystem();

protected:

	/**
	 *	These attributes will be spawned and referenced in the asset manager
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
	TArray<FPTRAttributeDefinition> ConfigAttributes;

private:

	/**
	 *	Store all the spawned Attributes
	 */
	UPROPERTY(Transient)
	TSet<class UPTRAttributeItem*> DynamicAttributes;

	/**
	 *	Bundle asset containing all the Dynamic Attributes
	 */
	UPROPERTY()
	FAssetBundleData AssetData;

	void ReferenceAllAttributes();

	/** Add a new attribute to the AssetManager */
	void ReferenceAttributeItem(class UPTRAttributeItem* Item);
};