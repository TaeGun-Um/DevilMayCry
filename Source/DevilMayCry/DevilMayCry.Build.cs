// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;   // For Path.Combine 

public class DevilMayCry : ModuleRules
{
	public DevilMayCry(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "Slate", "SlateCore", "Sockets", "Networking", "OnlineSubsystem", "HTTP" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        // miniupnpc ThirdParty Path
        string ThirdPartyPath = Path.Combine(ModuleDirectory, "../../ThirdParty/miniupnpc");

        // miniupnpc ThirdParty Header
        PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "include"));

        // miniupnpc ThirdParty lib
        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "lib", "miniupnpc.lib"));

        // miniupnpc ThirdParty dll
        RuntimeDependencies.Add("$(BinaryOutputDir)/miniupnpc.dll", Path.Combine(ThirdPartyPath, "bin", "miniupnpc.dll"));

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
