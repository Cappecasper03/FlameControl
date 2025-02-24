// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class FlameControl : ModuleRules
{
	public FlameControl( ReadOnlyTargetRules Target ) : base( Target )
	{
		PublicIncludePaths.Add( Path.Combine( EngineDirectory,  "Source", "Runtime/Launch/Public" ) );
		PrivateIncludePaths.Add( Path.Combine( EngineDirectory, "Source", "Runtime/Launch/Private" ) );

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"AppFramework",
				"Core",
				"ApplicationCore",
				"Projects",
				"Slate",
				"SlateCore",
				"StandaloneRenderer",
				"DesktopPlatform",
			}
		);

		if( Target.IsInPlatformGroup( UnrealPlatformGroup.Linux ) )
		{
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"UnixCommonStartup"
				}
			);
		}
	}
}