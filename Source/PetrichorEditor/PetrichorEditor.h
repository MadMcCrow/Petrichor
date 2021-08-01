// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"


class PETRICHOREDITOR_API FPTREditorModule : public IModuleInterface
{
	public:
	// IModuleInterface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

};