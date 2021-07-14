// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PetrichorEditor : ModuleRules
{
	public PetrichorEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine"});
		PrivateDependencyModuleNames.AddRange((new []{ "InputCore", "UnrealEd", "ClassViewer", "Petrichor" }));
	}
}