// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameJam2024 : ModuleRules
{
	public GameJam2024(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

        PublicDependencyModuleNames.AddRange(new string[] { "AIModule", "NavigationSystem", "GameplayTasks", "UMG" });

        PrivateDependencyModuleNames.AddRange(new string[] {"Paper2D", "PaperZD" });

        PublicIncludePaths.AddRange(
        new string[] {
            "GameJam2024",
            "GameJam2024/Vincent",
            "GameJam2024/Max",
            "GameJam2024/Henry",
            "GameJam2024/Clayton",
        });
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
