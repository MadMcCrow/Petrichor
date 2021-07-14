// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Petrichor : ModuleRules
{
	public Petrichor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine",});

		PrivateDependencyModuleNames.AddRange((new []{ "InputCore", "AIModule" }));

		PrivateDependencyModuleNames.AddRange((new []{ "GameplayAbilities", "GameplayTags", "GameplayTasks" }));

		// Add support for networking
		PrivateDependencyModuleNames.Add("OnlineSubsystem");
		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

		// VR Support
		PrivateDependencyModuleNames.AddRange((new []{ "HeadMountedDisplay" }));
	}
}