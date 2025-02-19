﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "MainWindow.h"

#include "Framework/Application/SWindowTitleBar.h"
#include "Popup/PopupMenu.h"
#include "Popup/PopupWindow.h"
#include "StandaloneRenderer.h"

#if PLATFORM_WINDOWS
	#include "Windows/WindowsPlatformApplicationMisc.h"
#elif PLATFORM_LINUX
	#include "Linux/LinuxPlatformApplicationMisc.h"
#endif

TSharedPtr< SWindow > SMainWindow::MainWindow = nullptr;
bool                  SMainWindow::IsRunning  = false;

void SMainWindow::Run()
{
	TRACE_CPUPROFILER_EVENT_SCOPE( SMainWindow::Run );

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

	MainWindow = MakeWindow();
	FSlateApplication::Get().AddWindow( MainWindow.ToSharedRef() );

	constexpr float IdealFrameTime = 1.f / 60.f;
	while( !IsEngineExitRequested() )
	{
		TRACE_BEGIN_FRAME( TraceFrameType_Game );

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

		TRACE_END_FRAME( TraceFrameType_Game );
	}

	MainWindow.Reset();
	FSlateApplication::Shutdown();
}

void SMainWindow::OpenPopupWindow( const TSharedPtr< SWidget >& InContent )
{
	const TSharedRef< SWindow > Window = SNew( SWindow ).MinWidth( 400 ).MinHeight( 300 );
	Window->SetContent( SNew( SPopupWindow, Window, InContent ) );

	FSlateApplication::Get().AddModalWindow( Window, MainWindow.ToSharedRef() );
}

void SMainWindow::GetTitleBarContents( const TSharedRef< SWindow >& InWindow, FTitleBarData& OutLeftContent, FTitleBarData& OutCenterContent, FTitleBarData& OutRightContent )
{
	const TSharedRef< SWidget > WindowOverlay      = InWindow->GetChildren()->GetChildAt( 0 );
	const TSharedRef< SWidget > WindowVerticalBox1 = WindowOverlay->GetChildren()->GetChildAt( 3 );
	const TSharedRef< SWidget > WindowVerticalBox2 = WindowVerticalBox1->GetChildren()->GetChildAt( 0 );
	const TSharedRef< SWidget > WindowTitlebar     = WindowVerticalBox2->GetChildren()->GetChildAt( 0 );

	const TSharedRef< SWidget > TitlebarBorder   = WindowTitlebar->GetChildren()->GetChildAt( 0 );
	const TSharedRef< SWidget > TitlebarOverlay1 = TitlebarBorder->GetChildren()->GetChildAt( 0 );
	const TSharedRef< SWidget > TitlebarBox1     = TitlebarOverlay1->GetChildren()->GetChildAt( 1 );
	const TSharedRef< SWidget > TitlebarOverlay2 = TitlebarBox1->GetChildren()->GetChildAt( 0 );

	const TSharedRef< SWidget > TitlebarHorizontalBox1 = TitlebarOverlay2->GetChildren()->GetChildAt( 0 );
	const TSharedRef< SWidget > TitlebarBox2           = TitlebarHorizontalBox1->GetChildren()->GetChildAt( 1 );
	OutCenterContent.Parent                            = TitlebarHorizontalBox1;
	OutCenterContent.Content                           = TitlebarBox2->GetChildren()->GetChildAt( 0 );

	const TSharedRef< SWidget > TitlebarHorizontalBox2 = TitlebarOverlay2->GetChildren()->GetChildAt( 1 );

	const TSharedRef< SWidget > TitlebarHorizontalBox3 = TitlebarHorizontalBox2->GetChildren()->GetChildAt( 0 );
	OutLeftContent.Parent                              = TitlebarHorizontalBox2;
	OutLeftContent.Content                             = TitlebarHorizontalBox3->GetChildren()->GetChildAt( 0 );

	const TSharedRef< SWidget > TitlebarBox3 = TitlebarHorizontalBox2->GetChildren()->GetChildAt( 2 );
	OutRightContent.Parent                   = TitlebarHorizontalBox2;
	OutRightContent.Content                  = TitlebarBox3->GetChildren()->GetChildAt( 0 );
}

TSharedRef< SWindow > SMainWindow::MakeWindow()
{
	TSharedRef< SMainWindow > Window = SNew( SMainWindow ).ClientSize( FVector2D( 1000, 600 ) ).MinWidth( 600 ).MinHeight( 600 );

	FTitleBarData LeftContent;
	FTitleBarData CenterContent;
	FTitleBarData RightContent;
	GetTitleBarContents( Window, LeftContent, CenterContent, RightContent );

	// clang-format off
	TSharedPtr< SWidget > GitButton = SNew( SVerticalBox )
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew( SButton )
			.Text( FText::FromString( TEXT( "Clone" ) ) )
			.OnPressed_Lambda( []{ OpenPopupWindow( SNew( SButton ) ); } )
		]

		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew( SButton )
			.Text( FText::FromString( TEXT( "Init" ) ) )
			.OnPressed_Lambda( []{ OpenPopupWindow( SNew( SButton ) ); } )
		]
		
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew( SButton )
			.Text( FText::FromString( TEXT( "Open" ) ) )
			.OnPressed_Lambda( []{ OpenPopupWindow( SNew( SButton ) ); } )
		];

	TSharedPtr< SWidget > SvnButton = SNew( SVerticalBox )
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew( SButton )
			.Text( FText::FromString( TEXT( "Checkout" ) ) )
			.OnPressed_Lambda( []{ OpenPopupWindow( SNew( SButton ) ); } )
		]

		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew( SButton )
			.Text( FText::FromString( TEXT( "Create" ) ) )
			.OnPressed_Lambda( []{ OpenPopupWindow( SNew( SButton ) ); } )
		]
		
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew( SButton )
			.Text( FText::FromString( TEXT( "Open" ) ) )
			.OnPressed_Lambda( []{ OpenPopupWindow( SNew( SButton ) ); } )
		];
	
	const TSharedRef< SWidget > NewLeftContent = SNew( SHorizontalBox )
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew( SPopupMenu, GitButton )
			.Text( FText::FromString( "Git" ) )
		]

		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(  SPopupMenu, SvnButton )
			.Text( FText::FromString( "Svn" ) )
		];
	// clang-format on

	SHorizontalBox*                            LeftParent = reinterpret_cast< SHorizontalBox* >( LeftContent.Parent.Get() );
	const int32                                Index      = LeftParent->RemoveSlot( LeftContent.Content->GetParentWidget().ToSharedRef() );
	SHorizontalBox::FScopedWidgetSlotArguments LeftSlot   = LeftParent->InsertSlot( Index );
	LeftSlot.AttachWidget( NewLeftContent );

	STextBlock* CenterTextBlock = reinterpret_cast< STextBlock* >( CenterContent.Content.Get() );
	CenterTextBlock->SetText( FText::FromString( "FlameControl" ) );

	Window->SetContent( SNew( SImage ) );
	return Window;
}