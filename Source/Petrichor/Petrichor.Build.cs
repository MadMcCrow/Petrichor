// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Petrichor : ModuleRules
{
	public Petrichor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine",});

		PrivateDependencyModuleNames.AddRange((new []{ "InputCore", "GameplayTags", "HeadMountedDisplay" }));
	}
}