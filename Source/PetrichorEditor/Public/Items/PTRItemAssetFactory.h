// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "Factories/DataAssetFactory.h"
#include "PTRItemAssetFactory.generated.h"

/**
 *	Helper for Creating Items in Editor
 */
UCLASS()
class PETRICHOREDITOR_API UPTRItemAssetFactory : public UDataAssetFactory
{
	GENERATED_BODY()
public:

	// Default CTR.
	UPTRItemAssetFactory();

	virtual bool ConfigureProperties() override;

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

	virtual bool ShouldShowInNewMenu() const override;

	virtual FText GetDisplayName() const override;

	virtual uint32 GetMenuCategories() const override;

};