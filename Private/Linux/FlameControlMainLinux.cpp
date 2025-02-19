// Copyright Epic Games, Inc. All Rights Reserved.

#include "FlameControlApp.h"

/**
 * main(), called when the application is started
 */
int main( int argc, const char *argv[] )
{
	FString SavedCommandline;

	for ( int32 Option = 1; Option < argc; Option++ )
	{
		SavedCommandline += TEXT( " " );
		SavedCommandline += UTF8_TO_TCHAR( argv[ Option ] );
	}

	RunFlameControl( *SavedCommandline );
	return 0;
}
