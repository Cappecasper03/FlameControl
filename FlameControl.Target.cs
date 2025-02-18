// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

[SupportedPlatforms( "Win64", "Linux" )]
[SupportedConfigurations( UnrealTargetConfiguration.Debug, UnrealTargetConfiguration.Development, UnrealTargetConfiguration.Shipping )]
public sealed class FlameControlTarget : TargetRules
{
	public FlameControlTarget( TargetInfo Target ) : base( Target )
	{
		Type                     = TargetType.Program;
		LinkType                 = TargetLinkType.Monolithic;
		IncludeOrderVersion      = EngineIncludeOrderVersion.Latest;
		UndecoratedConfiguration = UnrealTargetConfiguration.Shipping;
		OptimizationLevel        = OptimizationMode.SizeAndSpeed;

		LaunchModuleName = "FlameControl";

		bLegalToDistributeBinary = true;
		bBuildDeveloperTools     = false;

		bCompileAgainstEngine      = false;
		bCompileAgainstCoreUObject = true;

		bUseLoggingInShipping = false;
		bHasExports           = false;
		bUseChecksInShipping  = false;

		bCompileICU = true;

		bEnableTrace = true;
	}
}