// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#include "Items/PTRItemAssetFactory.h"
#include "Items/PTRItem.h"
#include "ClassViewerModule.h"
#include "ClassViewer/Private/UnloadedBlueprintData.h"
#include "AssetTypeCategories.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Kismet2/SClassPickerDialog.h"


#define LOCTEXT_NAMESPACE "PTREditor"

class FPTRItemClassParentFilter : public IClassViewerFilter
{
public:
	FPTRItemClassParentFilter()
	{}

	// We don't want classes that follow those flags
	static const  EClassFlags DisallowedClassFlags =
	CLASS_Interface			|	CLASS_Abstract			|	CLASS_Transient			|
	CLASS_LayoutChanging	|	CLASS_Hidden			|	CLASS_Deprecated		|
	CLASS_HideDropDown		|	CLASS_NewerVersionExists;

	/** The results */
	TSet< const UClass* > AllowedChildrenClasses;

	virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override
	{
		return !InClass->HasAnyClassFlags(DisallowedClassFlags) && InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenClasses, InClass) != EFilterReturn::Failed;
	}

	virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef< const IUnloadedBlueprintData > InUnloadedClassData, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override
	{
		return !InUnloadedClassData->HasAnyClassFlags(DisallowedClassFlags) && InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenClasses, InUnloadedClassData) != EFilterReturn::Failed;
	}
};

UPTRItemAssetFactory::UPTRItemAssetFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UPTRItem::StaticClass();
}

bool UPTRItemAssetFactory::ConfigureProperties()
{
	// nullptr the DataAssetClass so we can check for selection
	DataAssetClass = nullptr;

	// Load the classviewer module to display a class picker
	FClassViewerModule& ClassViewerModule = FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer");

	// Fill in options
	FClassViewerInitializationOptions Options;
	Options.Mode = EClassViewerMode::ClassPicker;
	TSharedPtr<FPTRItemClassParentFilter> Filter = MakeShareable(new FPTRItemClassParentFilter);
	Options.ClassFilter = Filter;
	Filter->AllowedChildrenClasses.Add(SupportedClass);

	const FText TitleText = LOCTEXT("CreateDataAssetOptions", "Pick Data Asset Class");
	UClass* ChosenClass = nullptr;
	const bool bPressedOk = SClassPickerDialog::PickClass(TitleText, Options, ChosenClass, UDataAsset::StaticClass());

	if ( bPressedOk )
	{
		DataAssetClass = ChosenClass;
	}

	return bPressedOk;
}

UObject* UPTRItemAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	if (DataAssetClass != nullptr)
	{
		return NewObject<UDataAsset>(InParent, DataAssetClass, Name, Flags | RF_Transactional);
	}

	// if we have no data asset class, use the passed-in class instead
	check(Class->IsChildOf(UDataAsset::StaticClass()));
	return NewObject<UDataAsset>(InParent, Class, Name, Flags);
}

bool UPTRItemAssetFactory::ShouldShowInNewMenu() const
{
	return true;
}

FText UPTRItemAssetFactory::GetDisplayName() const
{
	return LOCTEXT("ItemName", "Petrichor Item");
}

uint32 UPTRItemAssetFactory::GetMenuCategories() const
{
	return EAssetTypeCategories::Gameplay;
}

#undef LOCTEXT_NAMESPACE
