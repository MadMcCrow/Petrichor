// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Petrichor : ModuleRules
{
	public Petrichor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new [] { "Core", "CoreUObject", "Engine",});

		PrivateDependencyModuleNames.AddRange((new []{ "InputCore", "AIModule" }));

		// We do not need GAS , mouaaaahahaha
		// PrivateDependencyModuleNames.AddRange((new []{ "GameplayAbilities", "GameplayTags", "GameplayTasks" }));

		// Movie player for cinematics, Loading screens, etc...
		PrivateDependencyModuleNames.AddRange((new []{ "MoviePlayer"}));

		// Add support for networking
		PrivateDependencyModuleNames.Add("OnlineSubsystem");
		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

		// VR Support
		PrivateDependencyModuleNames.AddRange((new []{ "HeadMountedDisplay" }));
	}
}