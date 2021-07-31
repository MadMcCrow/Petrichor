// Copyright Epic Games, Inc. All Rights Reserved.

#include "PetrichorEditor.h"

#include "Items/PTRSoftItemPathCustomization.h"

IMPLEMENT_MODULE(FPTREditorModule, PetrichorEditor);

void FPTREditorModule::StartupModule()
{
	// register SoftItemPath custom editor layout
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomPropertyTypeLayout("PTRSoftItemPath", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FPTRSoftItemPathCustomization::MakeInstance));
}

void FPTREditorModule::ShutdownModule()
{
	// unregister SoftItemPath custom editor layout
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomPropertyTypeLayout("PTRSoftItemPath");
}