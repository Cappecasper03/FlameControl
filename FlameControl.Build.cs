// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FlameControl : ModuleRules
{
	public FlameControl( ReadOnlyTargetRules Target ) : base( Target )
	{
		PublicIncludePathModuleNames.Add( "Launch" );

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"ApplicationCore",
				"Projects",
				"MessageLog",
				"InputCore",
				"Slate",
				"SlateCore",
				"StandaloneRenderer", 
				"DesktopPlatform",
			}
		);
	}
}