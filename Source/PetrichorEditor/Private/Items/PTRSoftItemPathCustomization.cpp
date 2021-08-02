// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#include "Items/PTRSoftItemPathCustomization.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "EditorClassUtils.h"
#include "PropertyHandle.h"
#include "PropertyCustomizationHelpers.h"
#include "Engine/AssetManager.h"
#include "Items/PTRSoftItemPath.h"


void FPTRSoftItemPathCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle,
                                                    FDetailWidgetRow& HeaderRow,
                                                    IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructPropertyHandle = InStructPropertyHandle;
	PathPropertyHandle   = StructPropertyHandle->GetChildHandle("ItemPath");
	UClass* MetaClass = FEditorClassUtils::GetClassFromString("PTRItem");
	FString StringValue;
	PathPropertyHandle->GetValueAsFormattedString(StringValue,EPropertyPortFlags::PPF_ExportCpp );
	if (StringValue != FString())
	{
		FAssetData StoredAsset;
		if (PathPropertyHandle->GetValue(StoredAsset) == FPropertyAccess::Success)
		{
			if (StoredAsset.GetClass())
			{
				MetaClass = StoredAsset.GetClass();
				ClassSelector = MetaClass;
			}
		}
	}
	else
	{
		MetaClass = FEditorClassUtils::GetClassFromString("PTRItem");
		if (ClassSelector.Get() == nullptr)
		{
			ClassSelector = MetaClass;
		}
	}

	// Set widget :
	HeaderRow
		.NameContent()
		[
			InStructPropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		.MinDesiredWidth(250.0f)
		.MaxDesiredWidth(0.0f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SClassPropertyEntryBox)
				.MetaClass(MetaClass)
				.RequiredInterface(nullptr)
				.AllowAbstract(true)
				.IsBlueprintBaseOnly(false)
				.AllowNone(false)
				.ShowTreeView(true)
				.HideViewOptions(false)
				.ShowDisplayNames(true)
				.SelectedClass(this, &FPTRSoftItemPathCustomization::OnGetClass)
				.OnSetClass(this, &FPTRSoftItemPathCustomization::OnSetClass)
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				// Add an object entry box.  Even though this isn't an object entry, we will simulate one
				SNew(SObjectPropertyEntryBox)
				.OnShouldFilterAsset(this, &FPTRSoftItemPathCustomization::OnFilterItem)
				.AllowedClass(ClassSelector.Get())
				.DisplayThumbnail(false)
				.EnableContentPicker(true)
				.PropertyHandle(PathPropertyHandle)
				.OnObjectChanged(this, &FPTRSoftItemPathCustomization::OnSetItem)
				.ThumbnailPool(StructCustomizationUtils.GetThumbnailPool())
			]
		];

	// This avoids making duplicate reset boxes
	StructPropertyHandle->MarkResetToDefaultCustomized();
}

void FPTRSoftItemPathCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle,
                                                      IDetailChildrenBuilder& StructBuilder,
                                                      IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

const UClass* FPTRSoftItemPathCustomization::OnGetClass() const
{
	if (ClassSelector.IsValid())
		return ClassSelector.Get();

	// just limit to PTRItem
	return FEditorClassUtils::GetClassFromString("PTRItem");
}

void FPTRSoftItemPathCustomization::OnSetClass(const UClass* NewClass)
{
	const UClass* ItemClass = FEditorClassUtils::GetClassFromString("PTRItem");
	if (NewClass == nullptr )
	{
		ClassSelector = MakeWeakObjectPtr(const_cast<UClass*>(ItemClass));
	}
	else
	{
		if (NewClass->IsChildOf(ItemClass))
		{
			ClassSelector = MakeWeakObjectPtr(const_cast<UClass*>(NewClass));
		}
		else
		{
			// should log an error
			ClassSelector = MakeWeakObjectPtr(const_cast<UClass*>(ItemClass));
		}
	}
}

void FPTRSoftItemPathCustomization::OnSetItem(const FAssetData& NewAsset)
{
	if (UAssetManager* Manager = UAssetManager::GetIfValid())
	{
		// get asset info
		auto PrimaryItemID = NewAsset.GetPrimaryAssetId();
		auto Path = Manager->GetPrimaryAssetPath(PrimaryItemID);

		// try to find what this property is all about
		IPropertyHandle* StructProperty = StructPropertyHandle.Get();
		auto PathProp = FPTRSoftItemPath::StaticStruct()->FindPropertyByName("ItemPath");
	}
}

bool FPTRSoftItemPathCustomization::OnFilterItem(const FAssetData& AssetData)
{
	if (!AssetData.GetClass()->IsChildOf(ClassSelector.Get()))
		return true;
	// by default allow everyone
	return false;
}
