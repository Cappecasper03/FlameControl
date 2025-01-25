// Copyright Epic Games, Inc. All Rights Reserved.

#include "FlameControlApp.h"

/**
 * main(), called when the application is started
 */
int main( int argc, const char *argv[] )
{
	FString SavedCommandLine;

	for ( int32 Option = 1; Option < argc; Option++ )
	{
		SavedCommandLine += TEXT( " " );
		SavedCommandLine += UTF8_TO_TCHAR( argv[ Option ] );
	}

	RunFlameControl( *SavedCommandLine );
	return 0;
}
