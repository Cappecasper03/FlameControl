// Copyright Epic Games, Inc. All Rights Reserved.

#include "FlameControlApp.h"

#include "Framework/Application/SlateApplication.h"
#include "Framework/Docking/TabManager.h"
#include "Main/FMainApp.h"
#include "Runtime/Launch/Public/RequiredProgramMainCPPInclude.h"
#include "StandaloneRenderer.h"

IMPLEMENT_APPLICATION( FlameControl, "FlameControl" );

DEFINE_LOG_CATEGORY( FlameControl );

int RunFlameControl( const TCHAR* InCommandline )
{
	TRACE_CPUPROFILER_EVENT_SCOPE( RunFlameControl );

	FTaskTagScope TaskTagScope( ETaskTag::EGameThread );

#if !UE_BUILD_SHIPPING
	// If "-waitforattach" or "-WaitForDebugger" was specified, halt startup and wait for a debugger to attach before continuing
	if( FParse::Param( InCommandline, TEXT( "waitforattach" ) ) || FParse::Param( InCommandline, TEXT( "WaitForDebugger" ) ) )
	{
		while( !FPlatformMisc::IsDebuggerPresent() ) {}
		UE_DEBUG_BREAK();
	}
#endif

#if !UE_GAME
	// Flags this program as staged so that the saved folder is inside the project directory
	const FString Filename = FPaths::Combine( FPaths::EngineConfigDir(), FString::Printf( TEXT( "StagedBuild_%s.ini" ), FApp::GetProjectName() ) );
	FFileHelper::SaveStringToFile( Filename, *Filename );
#endif

	// start up the main loop
	GEngineLoop.PreInit( InCommandline );

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

	while( !IsEngineExitRequested() )
	{
		TRACE_CPUPROFILER_EVENT_SCOPE( RunFlameControl::Tick );
		TRACE_BEGIN_FRAME( TraceFrameType_Game );

		BeginExitIfRequested();

		FApp::SetCurrentTime( FPlatformTime::Seconds() );
		FApp::SetDeltaTime( FApp::GetCurrentTime() - FApp::GetLastTime() );
		FApp::UpdateLastTime();

		FTaskGraphInterface::Get().ProcessThreadUntilIdle( ENamedThreads::GameThread );
		FStats::AdvanceFrame( false );
		FTSTicker::GetCoreTicker().Tick( FApp::GetDeltaTime() );
		FSlateApplication::Get().PumpMessages();
		FSlateApplication::Get().Tick();

		{
			TRACE_CPUPROFILER_EVENT_SCOPE( RunFlameControl::Tick::Sleep );
			static constexpr double IdealDeltaTime = 1.f / 60.f;
			FPlatformProcess::Sleep( FMath::Max< double >( 0, IdealDeltaTime - ( FPlatformTime::Seconds() - FApp::GetLastTime() ) ) );
		}

		GFrameCounter++;

		TRACE_END_FRAME( TraceFrameType_Game );
	}

#if !UE_GAME
	IFileManager::Get().Delete( *Filename );
#endif

	RequestEngineExit( TEXT( "FlameControlApp RequestExit" ) );

	FCoreDelegates::OnExit.Broadcast();
	FSlateApplication::Shutdown();
	FModuleManager::Get().UnloadModulesAtShutdown();

	GEngineLoop.AppPreExit();
	GEngineLoop.AppExit();

	return 0;
}