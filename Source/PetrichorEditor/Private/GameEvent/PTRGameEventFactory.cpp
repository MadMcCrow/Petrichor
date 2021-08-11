// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#include "GameEvent/PTRGameEventFactory.h"
#include "AssetTypeCategories.h"
#include "ClassIconFinder.h"
#include "ClassViewerModule.h"
#include "ClassViewer/Private/UnloadedBlueprintData.h"
#include "GameEvent/PTRGameEvent.h"
#include "GameEvent/PTRGameEventBlueprint.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Kismet2/SClassPickerDialog.h"

//#define LOCTEXT_NAMESPACE "PTREditor"
#define LOCTEXT_NAMESPACE "PTRGameEventEditor"

class FPTRGameEventClassParentFilter : public IClassViewerFilter
{
public:
	FPTRGameEventClassParentFilter()
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



UPTRGameEventFactory::UPTRGameEventFactory() : Super()
{
	bCreateNew		= true;
	bEditAfterNew	= true;
	SupportedClass	= UPTRGameEventBlueprint::StaticClass();
	ParentClass		= UPTRGameEvent::StaticClass();
}

UObject* UPTRGameEventFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags,	UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	// Make sure we are trying to factory a blueprint, then create and init one
	if (!ParentClass->IsChildOf(UPTRGameEvent::StaticClass()))
	{
		FText ClassName = (ParentClass != nullptr) ? FText::FromString(ParentClass->GetName()) : LOCTEXT("Null", "(null)");
		FMessageDialog::Open(EAppMsgType::Ok, FText::Format(LOCTEXT("CannotCreateBlueprintFromClass", "Cannot create a Game Event blueprint based on the class '{0}'."), ClassName));
		return nullptr;
	}
	if (!FKismetEditorUtilities::CanCreateBlueprintOfClass(ParentClass))
	{
		FText ClassName = (ParentClass != nullptr) ? FText::FromString(ParentClass->GetName()) : LOCTEXT("Null", "(null)");
		FMessageDialog::Open(EAppMsgType::Ok, FText::Format(LOCTEXT("CannotCreateBlueprintFromClass", "Cannot create a Game Event blueprint based on the class '{0}'."), ClassName));
		return nullptr;
	}

	{
		return FKismetEditorUtilities::CreateBlueprint(ParentClass, InParent, Name, BPTYPE_Normal, UPTRGameEventBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), CallingContext);
	}
}

UObject* UPTRGameEventFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return FactoryCreateNew(Class, InParent, Name, Flags, Context, Warn, NAME_None);
}

bool UPTRGameEventFactory::ConfigureProperties()
{
	// nullptr the DataAssetClass so we can check for selection
	ParentClass = UPTRGameEvent::StaticClass();

	// Load the classviewer module to display a class picker
	FClassViewerModule& ClassViewerModule = FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer");

	// Fill in options
	FClassViewerInitializationOptions Options;
	Options.Mode = EClassViewerMode::ClassPicker;
	TSharedPtr<FPTRGameEventClassParentFilter> Filter = MakeShareable(new FPTRGameEventClassParentFilter);
	Options.ClassFilter = Filter;
	Filter->AllowedChildrenClasses.Add(ParentClass);

	const FText TitleText = LOCTEXT("CreateGameEventOption", "Pick GameEventParent Class");
	UClass* ChosenClass = nullptr;
	const bool bPressedOk = SClassPickerDialog::PickClass(TitleText, Options, ChosenClass, UDataAsset::StaticClass());

	if ( bPressedOk )
	{
		ParentClass = ChosenClass;
	}

	return bPressedOk;
}

FString UPTRGameEventFactory::GetDefaultNewAssetName() const
{
	return UPTRGameEvent::StaticClass()->GetName();
}

FName UPTRGameEventFactory::GetNewAssetThumbnailOverride() const
{
	return FSlateIconFinder::FindCustomIconForClass(UPTRGameEvent::StaticClass(),TEXT("ClassThumbnail")).GetStyleName();
}

FText UPTRGameEventFactory::GetDisplayName() const
{
	return LOCTEXT("GameEventName", "Petrichor GameEvent");
}

uint32 UPTRGameEventFactory::GetMenuCategories() const
{
	return EAssetTypeCategories::Gameplay;
}

FText UPTRGameEventFactory::GetToolTip() const
{
	return LOCTEXT("GameEventTooltip", "Game Events are UObject that trigger Gameplay mechanics. They allow nice replication and allow making systemic scripting");
}

#undef LOCTEXT_NAMESPACE
