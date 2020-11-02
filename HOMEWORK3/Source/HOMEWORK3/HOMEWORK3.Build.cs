// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HOMEWORK3 : ModuleRules
{
	public HOMEWORK3(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
