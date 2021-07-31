// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"

class IPropertyHandle;

/**
 * Customizes a PTRSoftItemPath to improve selection for items
 */
class FPTRSoftItemPathCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance()
	{
		return MakeShareable( new FPTRSoftItemPathCustomization );
	}

	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;
	virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;

private:
	/**
	 * Handle to the actual Path property being edited
	 */
	TSharedPtr<IPropertyHandle> StructPropertyHandle;

	/**
	* Handle to the actual Path property being edited
	*/
	TSharedPtr<IPropertyHandle> PathPropertyHandle;

	/**
	 *	The class to which we're restricting
	 */
	 TWeakObjectPtr<UClass> ClassSelector = nullptr;


protected:
	const UClass* OnGetClass() const;

	void OnSetClass(const UClass* NewClass);

	void OnSetItem(const FAssetData& NewAsset);

	bool OnFilterItem(const FAssetData& AssetData);
};