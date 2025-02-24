// Copyright Epic Games, Inc. All Rights Reserved.

#include "FlameControlApp.h"

#include "Framework/Application/SlateApplication.h"
#include "Framework/Docking/TabManager.h"
#include "Main/FMainApp.h"
#include "Runtime/Launch/Public/RequiredProgramMainCPPInclude.h"
#include "StandaloneRenderer.h"

IMPLEMENT_APPLICATION( FlameControl, "FlameControl" );

DEFINE_LOG_CATEGORY( FlameControl );

int RunFlameControl( const TCHAR* Commandline )
{
	TRACE_CPUPROFILER_EVENT_SCOPE( RunFlameControl );

	FTaskTagScope TaskTagScope( ETaskTag::EGameThread );

	// start up the main loop
	GEngineLoop.PreInit( Commandline );

	// Make sure all UObject classes are registered and default properties have been initialized
	ProcessNewlyLoadedUObjects();

	// Tell the module manager it may now process newly-loaded UObjects when new C++ modules are loaded
	FModuleManager::Get().StartProcessingNewlyLoadedObjects();

	// Crank up a normal Slate application using the platform's standalone renderer
	FSlateApplication::InitializeAsStandaloneApplication( GetStandardStandaloneRenderer() );
	FSlateApplication::InitHighDPI( true );

	// Set the application name
	FGlobalTabmanager::Get()->SetApplicationTitle( FText::FromString( "FlameControl" ) );

	// launch the main window of the FlameControl application
	FSlateApplication::Get().AddWindow( FMainApp::MakeWindow() );

	constexpr double IdealFrameTime = 1.f / 60.f;
	while( !IsEngineExitRequested() )
	{
		TRACE_CPUPROFILER_EVENT_SCOPE( RunFlameControl::Tick );
		TRACE_BEGIN_FRAME( TraceFrameType_Game );

		BeginExitIfRequested();

		const double DeltaTime = FApp::GetDeltaTime();
		FTaskGraphInterface::Get().ProcessThreadUntilIdle( ENamedThreads::GameThread );
		FStats::AdvanceFrame( false );
		FTSTicker::GetCoreTicker().Tick( DeltaTime );
		FSlateApplication::Get().PumpMessages();
		FSlateApplication::Get().Tick();
		FPlatformProcess::Sleep( FMath::Max< double >( 0, IdealFrameTime - DeltaTime ) );

		GFrameCounter++;
	}

	FCoreDelegates::OnExit.Broadcast();
	FSlateApplication::Shutdown();
	FModuleManager::Get().UnloadModulesAtShutdown();

	GEngineLoop.AppPreExit();
	GEngineLoop.AppExit();

	return 0;
}