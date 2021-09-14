// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

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

	// parametric CTR for conversion
	FPTRSoftItemPath(const FPrimaryAssetId& AssetID);

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

	/** Serializer to simplify it's serialisation */
	// Causes errors
	bool Serialize(FArchive& Ar)
	{
		Ar << ItemPath;
		return true;
	}

	/** Serializer to simplify it's serialisation */
	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
	{
		Ar << ItemPath;
		return true;
	}

	friend uint32 GetTypeHash(const FPTRSoftItemPath& SoftItem)
	{
		return GetTypeHash(SoftItem.ItemPath);
	}

	bool operator==(const FPTRSoftItemPath& rhs) const
	{
		return rhs.ItemPath == ItemPath;
	}

	// Get item class easier
	TSubclassOf<UPTRItem> GetClass() const;
};


 // register the serialiser for the Soft Item Path
template<>
struct TStructOpsTypeTraits<FPTRSoftItemPath> : public TStructOpsTypeTraitsBase2<FPTRSoftItemPath>
{
	enum
	{
		WithSerializer	= true, // might causes errors
		WithNetSerializer	= true,
	};
};





/**
 *	Functions for using FPTRSoftItemPath in Blueprint
 *	@see FPTRSoftItemPath
 */
UCLASS( ClassGroup=(PTR), Category="Petrichor|Items")
class PETRICHOR_API UPTRSoftItemPathLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	 * Function to try to load an Item based on it's path
	 * @param InPath The soft Item path
	 * @return the loaded item or nullptr if failed
	 */
	UFUNCTION(BlueprintCallable, Category="SoftItemPath",  meta=(DisplayName = "Try Load"))
	static class UPTRItem* TryLoadSoftItemPath(const FPTRSoftItemPath& InPath);

	/**
	 * Function to auto-convert FPTRSoftItemPath to String
	 * @param InPath The soft Item path
	 * @return the string text
	 */
	UFUNCTION(BlueprintPure, Category="SoftItemPath", meta=(DisplayName = "To String",  CompactNodeTitle = "->", BlueprintAutocast , Keywords = "String"))
	static FString SoftItemPathToString(const FPTRSoftItemPath& InPath);

	/**
	 * Function to auto-convert FPTRSoftItemPath to Soft Pointer/Reference
	 * @param InPath The soft Item path
	 * @return the Soft Pointer/Reference
	 */
	UFUNCTION(BlueprintPure, Category="SoftItemPath", meta=(DisplayName = "To Soft Object", CompactNodeTitle = "->", BlueprintAutocast , Keywords = "Soft Reference"))
	static TSoftObjectPtr<UPTRItem> SoftItemPathToSoftObject(const FPTRSoftItemPath& InPath);

	/**
	 * Function to auto-convert FPTRSoftItemPath to Soft path
	 * @param InPath The soft Item path
	 * @return the softObject  Path
	 */
	UFUNCTION(BlueprintPure, Category="SoftItemPath", meta=(DisplayName = "To Soft Path", CompactNodeTitle = "->", BlueprintAutocast , Keywords = "Soft Path"))
	static FSoftObjectPath SoftItemPathToSoftPath(const FPTRSoftItemPath& InPath);

	/**
	 * Function to auto-convert FPTRSoftItemPath Soft Pointer/Reference
	 * @param InPtr The soft Object ptr
	 * @return the Item Path
	 */
	UFUNCTION(BlueprintPure, Category="SoftItemPath", meta=(DisplayName = "From Soft Object", CompactNodeTitle = "->", BlueprintAutocast , Keywords = "Soft Reference"))
	static FPTRSoftItemPath SoftItemPathFromSoftObject(const TSoftObjectPtr<UPTRItem>& InPtr);

	/**
	 * Function to auto-convert FPTRSoftItemPath from Soft Path
	 * @param InPath The soft path
	 * @return the Item Path
	 */
	UFUNCTION(BlueprintPure, Category="SoftItemPath", meta=(DisplayName = "From Soft Path", CompactNodeTitle = "->", BlueprintAutocast , Keywords = "Soft Path"))
	static FPTRSoftItemPath SoftItemPathFromSoftPath(const FSoftObjectPath& InPath);

	/**
	 * Function to auto-convert FPTRSoftItemPath to FPrimaryAssetId
	 * @param InPath The item path
	 * @return the primary asset ID
	 */
	UFUNCTION(BlueprintPure, Category="SoftItemPath", meta=( DisplayName = "To Primary Asset ID", CompactNodeTitle = "->", BlueprintAutocast , Keywords = "Soft Path"))
	static FPrimaryAssetId SoftItemPathToAssetID(const FPTRSoftItemPath& InPath);

	/**
	* Function to auto-convert FPTRSoftItemPath from FPrimaryAssetId
	* @param InID The AssetId
	* @return the Item Path
	*/
	UFUNCTION(BlueprintPure, Category="SoftItemPath", meta=( DisplayName = "From Primary Asset ID", CompactNodeTitle = "->", BlueprintAutocast , Keywords = "Soft Path"))
	static FPTRSoftItemPath SoftItemPathFromAssetID(const FPrimaryAssetId& InID);




};
