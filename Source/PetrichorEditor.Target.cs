// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class PetrichorEditorTarget : TargetRules
{
	public PetrichorEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("Petrichor");
		ExtraModuleNames.Add("PetrichorEditor");
	}
}
