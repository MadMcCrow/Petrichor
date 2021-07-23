// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "Attributes/PTRAttributeSubsystem.h"
#include "PTRAssetManager.h"
#include "Attributes/PTRAttributeItem.h"
#include "Engine/AssetManager.h"

DEFINE_LOG_CATEGORY(LogAttributeSubsystem);

UPTRAttributeSubsystem::UPTRAttributeSubsystem() : Super()
{
	DynamicAttributes.Empty();
	AssetData.Reset();
}


void UPTRAttributeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if(UPTRAssetManager::IsAssetManagerClass())
	{
		UPTRAssetManager::AssetManagerReady.AddUObject(this, &UPTRAttributeSubsystem::ReferenceAllAttributes);
	}
	else
	{
#if !UE_BUILD_SHIPPING
	UE_LOG(LogAttributeSubsystem, Warning, TEXT("PTRAsset manager is not the asset manager class, attributes will not work"));
#endif //!UE_BUILD_SHIPPING
		ReferenceAllAttributes();
	}
}

void UPTRAttributeSubsystem::Deinitialize()
{
	AssetData.Reset();
	for (auto AttributeItr : DynamicAttributes)
	{
		AttributeItr->BeginDestroy();
	}
	DynamicAttributes.Empty();
}

FPrimaryAssetId UPTRAttributeSubsystem::GetAttributeID(FName InternalName) const
{
	for (UPTRAttributeItem* AttributeItr : DynamicAttributes)
	{
		if (AttributeItr && AttributeItr->InternalName == InternalName)
		{
			return AttributeItr->GetPrimaryAssetId();
		}
	}
	return FPrimaryAssetId();
}

FPrimaryAssetId UPTRAttributeSubsystem::GetAttributeID(UClass* AttributeClass) const
{
	for (UPTRAttributeItem* AttributeItr : DynamicAttributes)
	{
		if (AttributeItr && AttributeItr->StaticClass() == AttributeClass)
		{
			return AttributeItr->GetPrimaryAssetId();
		}
	}
	return FPrimaryAssetId();
}

FSoftObjectPath UPTRAttributeSubsystem::GetAttribute(FName InternalName) const
{
	for (UPTRAttributeItem* AttributeItr : DynamicAttributes)
	{
		if (AttributeItr && AttributeItr->InternalName == InternalName)
		{
			return FSoftObjectPath(AttributeItr);
		}
	}
	return FSoftObjectPath();
}

FSoftObjectPath UPTRAttributeSubsystem::GetAttribute(UClass* AttributeClass) const
{
	for (UPTRAttributeItem* AttributeItr : DynamicAttributes)
	{
		if (AttributeItr && AttributeItr->StaticClass() == AttributeClass)
		{
			return FSoftObjectPath(AttributeItr);
		}
	}
	return FSoftObjectPath();
}

UPTRAttributeSubsystem* UPTRAttributeSubsystem::GetAttributeSubsystem()
{
	return GEngine->GetEngineSubsystem<UPTRAttributeSubsystem>();
}

void UPTRAttributeSubsystem::ReferenceAllAttributes()
{
	// first all classes
	for (TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt)
	{
		UClass* Class = *ClassIt;
		// Ignore invalid classes
		if (Class->HasAnyClassFlags(CLASS_Deprecated | CLASS_NewerVersionExists | CLASS_Abstract | CLASS_LayoutChanging) ||
			(Class->HasAnyFlags(RF_Transient) && Class->HasAnyClassFlags(CLASS_CompiledFromBlueprint)))
		{
			continue;
		}

		// Check this class is a subclass of Base
		if (!Class->IsChildOf(UPTRAttributeItem::StaticClass()))
		{
			continue;
		}

		const auto NewAttribute = Cast<UPTRAttributeItem>(Class->GetDefaultObject());
		if (NewAttribute)
		{
			ReferenceAttributeItem(NewAttribute);
		}
	}

	// Then all non classes, defined by FPTRAttributeDefinition
	for (auto DefinitionItr : ConfigAttributes)
	{
		const UClass* AttributeClass = UPTRAttributeItem::StaticClass();
		auto NewAttribute = Cast<UPTRAttributeItem>(AttributeClass->GetDefaultObject());
		if (NewAttribute)
		{
			NewAttribute->InternalName = DefinitionItr.InternalName;
			NewAttribute->DisplayName  = DefinitionItr.DisplayName;
			ReferenceAttributeItem(NewAttribute);
		}
	}
}

void UPTRAttributeSubsystem::ReferenceAttributeItem(UPTRAttributeItem* Item)
{
	if (Item)
	{
		if (UAssetManager* Manager = UAssetManager::GetIfValid())
		{

			const auto ID = Item->GetPrimaryAssetId();
			const auto Path = FSoftObjectPath(Item);

			// Try to add to manager
			if (Manager->AddDynamicAsset(ID,Path, AssetData))
			{
				AssetData.AddBundleAsset("Attributes",Item);
				DynamicAttributes.Add(Item);
				Manager->LoadPrimaryAsset(ID);
			}
		}
	}
}