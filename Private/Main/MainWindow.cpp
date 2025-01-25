// Fill out your copyright notice in the Description page of Project Settings.

#include "MainWindow.h"

#include "Framework/Application/SWindowTitleBar.h"
#include "StandaloneRenderer.h"
#include "TitleBar.h"

#if PLATFORM_WINDOWS
	#include "Windows/WindowsPlatformApplicationMisc.h"
#elif PLATFORM_LINUX
	#include "Linux/LinuxPlatformApplicationMisc.h"
#endif

bool SMainWindow::IsRunning = false;

SMainWindow::SMainWindow()
{}

SMainWindow::~SMainWindow()
{}

void SMainWindow::Run()
{
	if( IsRunning )
		return;

	TSharedRef< FSlateApplication >    Slate         = FSlateApplication::Create( MakeShareable( FPlatformApplicationMisc::CreateApplication() ) );
	const TSharedRef< FSlateRenderer > SlateRenderer = GetStandardStandaloneRenderer();

	if( !FSlateApplication::Get().InitializeRenderer( SlateRenderer, true ) )
	{
		FSlateApplication::Shutdown();
		return;
	}

	IsRunning = true;
	FSlateApplication::Get().SetExitRequestedHandler( FSimpleDelegate::CreateLambda( [] { RequestEngineExit( TEXT( "OnRequestExit" ) ); } ) );

	FSlateApplication::Get().AddWindow( CreateWindow() );

	constexpr float IdealFrameTime = 1.f / 60.f;
	while( !IsEngineExitRequested() )
	{
		static double ActualDeltaTime = IdealFrameTime;
		static double LastTime        = FPlatformTime::Seconds();

		FTaskGraphInterface::Get().ProcessThreadUntilIdle( ENamedThreads::GameThread );
		FTSTicker::GetCoreTicker().Tick( ActualDeltaTime );

		FSlateApplication::Get().PumpMessages();
		FSlateApplication::Get().Tick();

		FPlatformProcess::Sleep( FMath::Max< float >( 0, IdealFrameTime - ( FPlatformTime::Seconds() - LastTime ) ) );

		const double AppTime = FPlatformTime::Seconds();
		ActualDeltaTime      = AppTime - LastTime;
		LastTime             = AppTime;
	}

	FSlateApplication::Shutdown();
}

TSharedRef< SWindow > SMainWindow::CreateWindow()
{
	// clang-format off
	TSharedRef< SMainWindow > Window = SNew( SMainWindow )
		.ClientSize( FVector2D( 1000, 600 ) )
		.MinWidth( 600 )
		.MinHeight( 600 )
		.CreateTitleBar( false )
		[
			SNew( SVerticalBox )

			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew( STitleBar )
			]

			+ SVerticalBox::Slot()
			.FillHeight( 1 )
			[
				SNew( SImage )
			]
		];
	// clang-format on

	return Window;
}