// Copyright Epic Games, Inc. All Rights Reserved.

#include "FlameControlApp.h"

#include "Main/MainWindow.h"
#include "RequiredProgramMainCPPInclude.h"

IMPLEMENT_APPLICATION( FlameControl, "FlameControl" );

DEFINE_LOG_CATEGORY( FlameControlLog );

void RunFlameControl( const TCHAR* InCommandline )
{
#if !PLATFORM_MAC
	FTaskTagScope ThreadScope( ETaskTag::EGameThread ); // Main thread is the game thread.
#endif

#if !( UE_BUILD_SHIPPING )
	// If "-waitforattach" or "-WaitForDebugger" was specified, halt startup and wait for a debugger to attach before continuing
	if( FParse::Param( InCommandline, TEXT( "waitforattach" ) ) || FParse::Param( InCommandline, TEXT( "WaitForDebugger" ) ) )
	{
		while( !FPlatformMisc::IsDebuggerPresent() ) {}
		UE_DEBUG_BREAK();
	}
#endif

	// Override the stack size for the thread pool.
	FQueuedThreadPool::OverrideStackSize = 256 * 1024;

	// Initialize the engine.
	const FString FinalCommandLine( InCommandline );
	GEngineLoop.PreInit( *FinalCommandLine );
	check( GConfig && GConfig->IsReadyForUse() );

	// Make sure all UObject classes are registered and default properties have been initialized
	ProcessNewlyLoadedUObjects();

	// Tell the module manager is may now process newly-loaded UObjects when new C++ modules are loaded
	FModuleManager::Get().StartProcessingNewlyLoadedObjects();

	// Load internal Concert plugins in the pre-default phase
	IPluginManager::Get().LoadModulesForEnabledPlugins( ELoadingPhase::PreDefault );

	// Load Concert Sync plugins in default phase
	IPluginManager::Get().LoadModulesForEnabledPlugins( ELoadingPhase::Default );

	SMainWindow::Run();

	RequestEngineExit( TEXT( "FlameControlApp RequestExit" ) );

	// Allow the game thread to finish processing any latent tasks.
	FTaskGraphInterface::Get().ProcessThreadUntilIdle( ENamedThreads::GameThread );

	FEngineLoop::AppPreExit();
	FModuleManager::Get().UnloadModulesAtShutdown();

	FEngineLoop::AppExit();
}
