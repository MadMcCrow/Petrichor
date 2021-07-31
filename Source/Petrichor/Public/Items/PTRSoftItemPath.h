// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "PTRSoftItemPath.generated.h"

// forward declaration
class UPTRItem;

/**
 *	Class to expose items to blueprint.
 *	This is a wrapper around soft object path constraining to Items
 */
USTRUCT(BlueprintType, Category="Petrichor|Items", meta=(ShowOnlyInnerProperties))
struct PETRICHOR_API FPTRSoftItemPath
{
	GENERATED_BODY()

	FPTRSoftItemPath()
	: ItemPath()
	{
	}

	// parametric CTR for conversion
	FPTRSoftItemPath(const FSoftObjectPath& ObjectPath)
	: ItemPath(ObjectPath)
	{
	}

	// parametric CTR for conversion
	FPTRSoftItemPath(const TSoftObjectPtr<UPTRItem>& ObjectPath)
	: ItemPath(ObjectPath.ToSoftObjectPath())
	{
	}

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowedClasses="PTRItem", AllowPrivateAccess="true"))
	FSoftObjectPath ItemPath;

public:

	/** Call Try load on Item Path */
	class UPTRItem* TryLoad() const;

	/** To String */
	FORCEINLINE FString ToString() const {return ItemPath.ToString();}

	/** to soft object pointer */
	TSoftObjectPtr<UPTRItem> ToSoftObject() const;

	/** to soft object pointer */
	FSoftObjectPath ToSoftPath() const;

	/** IsNull ItemPath shortcut */
	FORCEINLINE bool IsNull() const  {return ItemPath.IsNull();}

	/** IsValid ItemPath shortcut */
	FORCEINLINE bool IsValid() const  {return ItemPath.IsValid();}

	/** IsAsset ItemPath shortcut */
	FORCEINLINE bool IsAsset() const  {return ItemPath.IsAsset();}

	/** IsSubobject ItemPath shortcut */
	FORCEINLINE bool IsSubobject() const  {return ItemPath.IsSubobject();}

	// implicit conversion operator
	// To Soft Object Path
	FORCEINLINE operator FSoftObjectPath() const		{return ItemPath;}
	FORCEINLINE operator const FSoftObjectPath&() const	{return ItemPath;}
	// To Soft Object Ptr
	FORCEINLINE operator TSoftObjectPtr<UPTRItem>() const	{return ToSoftObject();}
	// To String
	FORCEINLINE operator FString() const	{return ToString();}

};


/**
 *	Functions for using FPTRSoftItemPath in Blueprint
 */
UCLASS( ClassGroup=(PTR), Category="Petrichor|Items")
class PETRICHOR_API UPTRSoftItemPathLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/** Try load soft Item path */
	UFUNCTION(BlueprintCallable, Category="SoftItemPath",  meta=(DisplayName = "Try Load"))
	class UPTRItem* TryLoadSoftItemPath(const FPTRSoftItemPath& InPath) const;

	/** convert to String */
	UFUNCTION(BlueprintCallable, Category="SoftItemPath", meta=(DisplayName = "To String",  CompactNodeTitle = "->", BlueprintAutocast , Keywords = "String"))
	FString SoftItemPathToString(const FPTRSoftItemPath& InPath) const;

	/** convert to Soft Pointer/Reference */
	UFUNCTION(BlueprintCallable, Category="SoftItemPath", meta=(DisplayName = "To Soft Object", CompactNodeTitle = "->", BlueprintAutocast , Keywords = "Soft Reference"))
	TSoftObjectPtr<UPTRItem> SoftItemPathToSoftObject(const FPTRSoftItemPath& InPath) const;

	/** convert to Soft Path */
	UFUNCTION(BlueprintCallable, Category="SoftItemPath", meta=(DisplayName = "To Soft Path", CompactNodeTitle = "->", BlueprintAutocast , Keywords = "Soft Path"))
	FSoftObjectPath SoftItemPathToSoftPath(const FPTRSoftItemPath& InPath) const;

	/** convert from Soft Pointer/Reference */
	UFUNCTION(BlueprintCallable, Category="SoftItemPath", meta=(DisplayName = "From Soft Object", CompactNodeTitle = "->", BlueprintAutocast , Keywords = "Soft Reference"))
	FPTRSoftItemPath SoftItemPathFromSoftObject(const TSoftObjectPtr<UPTRItem>& InPtr) const;

	/** convert from Soft Path */
	UFUNCTION(BlueprintCallable, Category="SoftItemPath", meta=(DisplayName = "From Soft Path", CompactNodeTitle = "->", BlueprintAutocast , Keywords = "Soft Path"))
	FPTRSoftItemPath SoftItemPathFromSoftPath(const FSoftObjectPath& InPath) const;


};