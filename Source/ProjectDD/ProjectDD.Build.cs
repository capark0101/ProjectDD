// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectDD : ModuleRules
{
	public ProjectDD(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PrivateIncludePaths.Add("ProjectDD");
		PrivateIncludePaths.Add("ProjectDD/Actor");
		PrivateIncludePaths.Add("ProjectDD/Character");
		PrivateIncludePaths.Add("ProjectDD/Actor/Pawn");
		PrivateIncludePaths.Add("ProjectDD/Game");
		PrivateIncludePaths.Add("ProjectDD/Input");
		PrivateIncludePaths.Add("ProjectDD/Manager");
		PrivateIncludePaths.Add("ProjectDD/StateMachine");
		PrivateIncludePaths.Add("ProjectDD/Table");
		PrivateIncludePaths.Add("ProjectDD/Table/Mapper");
		PrivateIncludePaths.Add("ProjectDD/Scene");
		PrivateIncludePaths.Add("ProjectDD/Level");
		PrivateIncludePaths.Add("ProjectDD/Unit");
		PrivateIncludePaths.Add("ProjectDD/Utils");
		PrivateIncludePaths.Add("ProjectDD/Widget");
        
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "CommonUI", "Kismet", "AIModule"});

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "EditorStyle" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
