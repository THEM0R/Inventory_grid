// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FPS_Inventory : ModuleRules
{
	public FPS_Inventory(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"SlateCore"
        });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"FPS_Inventory",
			"FPS_Inventory/Variant_Platforming",
			"FPS_Inventory/Variant_Platforming/Animation",
			"FPS_Inventory/Variant_Combat",
			"FPS_Inventory/Variant_Combat/AI",
			"FPS_Inventory/Variant_Combat/Animation",
			"FPS_Inventory/Variant_Combat/Gameplay",
			"FPS_Inventory/Variant_Combat/Interfaces",
			"FPS_Inventory/Variant_Combat/UI",
			"FPS_Inventory/Variant_SideScrolling",
			"FPS_Inventory/Variant_SideScrolling/AI",
			"FPS_Inventory/Variant_SideScrolling/Gameplay",
			"FPS_Inventory/Variant_SideScrolling/Interfaces",
			"FPS_Inventory/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
