// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "PTRAttributeComponent.generated.h"

/**
*	A simple struct to help generate many attributes from project settings
*/
USTRUCT(BlueprintType, Category="PTR|Attribute")
struct FPTRAttributeStats : public FTableRowBase
{
	GENERATED_BODY()

	/** The AttributeItem asset to use */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowedClasses="PTRAttributeItem"))
	FSoftObjectPath Attribute;

	/**
	 *	Base value correspond to how much is 100%
	 *	there's nothing preventing you to have more than 100% of it
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
	int32 BaseValue;


	// hash for Set and maps
	FORCEINLINE friend uint32 GetTypeHash(const FPTRAttributeStats& Key)
	{
		// basically call super
		return GetTypeHash(Key.Attribute);
	}

	FORCEINLINE friend bool operator==( const FPTRAttributeStats& LHS, const FPTRAttributeStats& RHS )
	{
		return GetTypeHash(LHS) == GetTypeHash(RHS);
	}

};


/**
 *	A component to help an actor to have attributes.
 *	it requieres to have an owner with the interface @class IPTRAttributeInterface
 */
UCLASS(ClassGroup=(PTR), MinimalAPI, Category="PTR|Attribute")
class UPTRAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPTRAttributeComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void OnRegister() override;

	/**
	 *	Retrieve inventory for further work
	 */
	UFUNCTION(BlueprintPure, Category="PTR|Attribute")
	class UPTRInventoryComponent* GetInventoryComponent() const;


	/**
	*	GetAttributeByName
	*	@return The amount of attribute that correspond to this name or 0
	*/
	UFUNCTION(BlueprintPure, Category="PTR|Attribute")
	int32 GetAttributeByName(FName InternalName) const;

	/**
	*	GetAttributeByClass
	*	@return The amount of attribute that correspond to this class or 0
	*/
	UFUNCTION(BlueprintPure, Category="PTR|Attribute")
	int32 GetAttributeByClass(UClass* AttributeClass) const;

	/**
	*	GetAttributeByName
	*	@return The amount of attribute that correspond to this name or 0
	*/
	UFUNCTION(BlueprintPure, Category="PTR|Attribute")
	int32 GetAttributeBaseByName(FName InternalName) const;

	/**
	*	GetAttributeByClass
	*	@return The amount of attribute that correspond to this class or 0
	*/
	UFUNCTION(BlueprintPure, Category="PTR|Attribute")
	int32 GetAttributeBaseByClass(UClass* AttributeClass) const;

protected:

	/**
	 *	Default Attribute for this Character/Object, etc.
	 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="PTR|Attribute")
	TArray<FPTRAttributeStats> DefaultAttributes;

	/**
	 *	A datatable that will fill @see DefaultAttributes automatically at @see OnRegister
	 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="PTR|Attribute",  meta=(AllowedClasses="Datatable"))
	FSoftObjectPath AttributesDatatable;



};