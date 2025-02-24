// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

[SupportedPlatforms( "Win64", "Linux" )]
[SupportedConfigurations( UnrealTargetConfiguration.Debug, UnrealTargetConfiguration.Development, UnrealTargetConfiguration.Shipping )]
public sealed class FlameControlTarget : TargetRules
{
	public FlameControlTarget( TargetInfo Target ) : base( Target )
	{
		Type                 = TargetType.Program;
		LinkType             = TargetLinkType.Monolithic;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion  = EngineIncludeOrderVersion.Latest;

		LaunchModuleName = "FlameControl";

		bCompileAgainstEngine      = false;
		bCompileAgainstCoreUObject = true;

		bUseLoggingInShipping = false;
		bHasExports           = false;
		bUseChecksInShipping  = false;

		bBuildDeveloperTools = false;

		bEnableTrace = true;
	}
}