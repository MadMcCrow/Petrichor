// Copyright Epic Games, Inc. All Rights Reserved.

#include "PetrichorEditor.h"
#include "AssetToolsModule.h"
#include "GameEvent/PTRGameEventTypeActions.h"	// GameEvent customization
#include "Items/PTRSoftItemPathCustomization.h"	// Soft Path for item

#define LOCTEXT_NAMESPACE "PetrichorEditor"

class FAssetToolsModule;
IMPLEMENT_MODULE(FPTREditorModule, PetrichorEditor);


void FPTREditorModule::StartupModule()
{
	// register SoftItemPath custom editor layout
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomPropertyTypeLayout("PTRSoftItemPath",
	                                                FOnGetPropertyTypeCustomizationInstance::CreateStatic(
		                                                &FPTRSoftItemPathCustomization::MakeInstance));

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	// creates a category named Petrichor in the advanced assets category
	// TODO: also use it in factories to have custom type to be listed in this category as well
	GameAssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("Petrichor")), LOCTEXT("PetrichorCategory", "Petrichor"));
	// Register class action for PTRGameEvent:
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FPTRGameEventTypeActions(GameAssetCategory)));


}

void FPTREditorModule::ShutdownModule()
{
	// unregister SoftItemPath custom editor layout
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomPropertyTypeLayout("PTRSoftItemPath");

	// No need to unload FAssetToolsModule as it's already unloaded at this point
	// Unregister class action for PTRGameEvent:
	// IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	// AssetTools.UnregisterAssetTypeActions(MakeShareable(new FPTRGameEventTypeActions(GameAssetCategory)));
}

#undef LOCTEXT_NAMESPACE
