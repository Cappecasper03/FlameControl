// Fill out your copyright notice in the Description page of Project Settings.

#include "SMainWindow.h"

#include "DesktopPlatformModule.h"
#include "Framework/Application/SWindowTitleBar.h"
#include "Git/SGitClone.h"
#include "Git/SGitInit.h"
#include "HAL/PlatformFileManager.h"
#include "IDesktopPlatform.h"
#include "Popup/SPopupMenu.h"
#include "Popup/SPopupWindow.h"
#include "StandaloneRenderer.h"

#if PLATFORM_WINDOWS
	#include "Windows/WindowsPlatformApplicationMisc.h"
#elif PLATFORM_LINUX
	#include "Linux/LinuxPlatformApplicationMisc.h"
#endif

TSharedPtr< SWindow > SMainWindow::MainWindow  = nullptr;
TSharedPtr< SWindow > SMainWindow::PopupWindow = nullptr;
bool                  SMainWindow::IsRunning   = false;

FString SMainWindow::GitExecutablePath = "";

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

	GitExecutablePath = GetExecutablePath( "git.exe" );

	IsRunning = true;
	FSlateApplication::Get().SetExitRequestedHandler( FSimpleDelegate::CreateLambda( [] { RequestEngineExit( TEXT( "OnRequestExit" ) ); } ) );

	MainWindow = MakeWindow();
	FSlateApplication::Get().AddWindow( MainWindow.ToSharedRef() );

	constexpr float IdealFrameTime = 1.f / 60.f;
	while( !IsEngineExitRequested() )
	{
		TRACE_CPUPROFILER_EVENT_SCOPE( SMainWindow::Run::Tick );
		TRACE_BEGIN_FRAME( TraceFrameType_Game );

		static double DeltaTime = IdealFrameTime;
		static double LastTime  = FPlatformTime::Seconds();

		FTaskGraphInterface::Get().ProcessThreadUntilIdle( ENamedThreads::GameThread );
		FTSTicker::GetCoreTicker().Tick( DeltaTime );

		FSlateApplication::Get().PumpMessages();
		FSlateApplication::Get().Tick();

		FPlatformProcess::Sleep( FMath::Max< float >( 0, IdealFrameTime - ( FPlatformTime::Seconds() - LastTime ) ) );

		const double AppTime = FPlatformTime::Seconds();
		DeltaTime            = AppTime - LastTime;
		LastTime             = AppTime;

		TRACE_END_FRAME( TraceFrameType_Game );
	}

	ClosePopupWindow();
	MainWindow.Reset();
	FSlateApplication::Shutdown();
}

void SMainWindow::OpenPopupWindow( const TSharedPtr< SWidget >& InContent )
{
	PopupWindow = SNew( SWindow ).MinWidth( 400 ).MinHeight( 300 );
	PopupWindow->SetContent( SNew( SPopupWindow, PopupWindow, InContent ) );

	FSlateApplication::Get().AddModalWindow( PopupWindow.ToSharedRef(), MainWindow.ToSharedRef() );
}

void SMainWindow::ClosePopupWindow()
{
	if( !PopupWindow.IsValid() )
		return;

	PopupWindow->RequestDestroyWindow();
	PopupWindow.Reset();
}

void SMainWindow::GetTitleBarContents( const TSharedRef< SWindow >& InWindow,
                                       TSharedPtr< SWidget >&       OutLeftContent,
                                       TSharedPtr< SWidget >&       OutCenterContent,
                                       TSharedPtr< SWidget >&       OutRightContent )
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
	OutCenterContent                                   = TitlebarBox2->GetChildren()->GetChildAt( 0 );

	const TSharedRef< SWidget > TitlebarHorizontalBox2 = TitlebarOverlay2->GetChildren()->GetChildAt( 1 );

	const TSharedRef< SWidget > TitlebarHorizontalBox3 = TitlebarHorizontalBox2->GetChildren()->GetChildAt( 0 );
	OutLeftContent                                     = TitlebarHorizontalBox3->GetChildren()->GetChildAt( 0 );

	const TSharedRef< SWidget > TitlebarBox3 = TitlebarHorizontalBox2->GetChildren()->GetChildAt( 2 );
	OutRightContent                          = TitlebarBox3->GetChildren()->GetChildAt( 0 );
}

void SMainWindow::ExecuteExecutableCommand( const FString& InExecutablePath, const FString& InCommand, const FString& InWorkingDirectory )
{
	AsyncTask(
		ENamedThreads::AnyBackgroundThreadNormalTask,
		[ = ]
		{
			uint32 ProcessId = 0;
			void*  WritePipe = nullptr;
			void*  ReadPipe  = nullptr;

			FPlatformProcess::CreatePipe( ReadPipe, WritePipe );
			FProcHandle ProcessHandle = FPlatformProcess::CreateProc( *InExecutablePath, *InCommand, false, true, true, &ProcessId, 0, *InWorkingDirectory, WritePipe, ReadPipe );

			if( !ProcessHandle.IsValid() )
			{
				FPlatformProcess::ClosePipe( ReadPipe, WritePipe );
				return;
			}

			FString Output = FPlatformProcess::ReadPipe( ReadPipe );
			while( !Output.IsEmpty() || FPlatformProcess::IsProcRunning( ProcessHandle ) )
			{
				TArray< FString > OutputLines;
				Output.ParseIntoArrayLines( OutputLines );

				for( auto Output1: OutputLines )
					UE_LOG( LogTemp, Log, TEXT( "%s" ), *Output1 );

				Output = FPlatformProcess::ReadPipe( ReadPipe );
			}

			Output = FPlatformProcess::ReadPipe( ReadPipe );
			FPlatformProcess::CloseProc( ProcessHandle );
			FPlatformProcess::ClosePipe( ReadPipe, WritePipe );
		} );
}

FString SMainWindow::OpenDirectoryDialog()
{
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if( !DesktopPlatform )
		return "";

	FString SelectedFolder;
	DesktopPlatform->OpenDirectoryDialog( FSlateApplication::Get().FindBestParentWindowHandleForDialogs( nullptr ), "Select Directory", "", SelectedFolder );

	return SelectedFolder;
}

TSharedRef< SWindow > SMainWindow::MakeWindow()
{
	TSharedRef< SMainWindow > Window = SNew( SMainWindow ).ClientSize( FVector2D( 1000, 600 ) ).MinWidth( 600 ).MinHeight( 600 );

	TSharedPtr< SWidget > LeftContent;
	TSharedPtr< SWidget > CenterContent;
	TSharedPtr< SWidget > RightContent;
	GetTitleBarContents( Window, LeftContent, CenterContent, RightContent );

	// clang-format off
	TSharedPtr< SWidget > GitButton = SNew( SVerticalBox )
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew( SButton )
			.Text( FText::FromString( TEXT( "Clone" ) ) )
			.OnPressed_Lambda( []{ OpenPopupWindow( SNew( SGitClone ) ); } )
		]

		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew( SButton )
			.Text( FText::FromString( TEXT( "Init" ) ) )
			.OnPressed_Lambda( []{ OpenPopupWindow( SNew( SGitInit ) ); } )
		]
		
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew( SButton )
			.Text( FText::FromString( TEXT( "Open" ) ) )
		];

	TSharedPtr< SWidget > SvnButton = SNew( SVerticalBox )
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew( SButton )
			.Text( FText::FromString( TEXT( "Checkout" ) ) )
		]

		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew( SButton )
			.Text( FText::FromString( TEXT( "Create" ) ) )
		]
		
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew( SButton )
			.Text( FText::FromString( TEXT( "Open" ) ) )
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

	SHorizontalBox*                            LeftParent = reinterpret_cast< SHorizontalBox* >( LeftContent->GetParentWidget().Get() );
	const int32                                Index      = LeftParent->RemoveSlot( LeftContent.ToSharedRef() );
	SHorizontalBox::FScopedWidgetSlotArguments LeftSlot   = LeftParent->InsertSlot( Index );
	LeftSlot.AttachWidget( NewLeftContent );

	STextBlock* CenterTextBlock = reinterpret_cast< STextBlock* >( CenterContent.Get() );
	CenterTextBlock->SetText( FText::FromString( "FlameControl" ) );

	SOverlay* CenterParentParent = reinterpret_cast< SOverlay* >( CenterContent->GetParentWidget()->GetParentWidget().Get() );
	SSpacer*  Spacer0            = reinterpret_cast< SSpacer* >( CenterParentParent->GetChildren()->GetChildAt( 0 ).ToSharedPtr().Get() );
	SSpacer*  Spacer2            = reinterpret_cast< SSpacer* >( CenterParentParent->GetChildren()->GetChildAt( 2 ).ToSharedPtr().Get() );

	Spacer0->SetSize( FVector2D( Spacer0->GetSize().X, 0 ) );
	Spacer2->SetSize( FVector2D( Spacer2->GetSize().X, 0 ) );

	Window->SetContent( SNew( SImage ) );
	return Window;
}

FString SMainWindow::GetExecutablePath( const FString& InExecutableName )
{
	const FString EnvironmentVariabelString = FPlatformMisc::GetEnvironmentVariable( *FString( "Path" ) );

	TArray< FString > EnvironmentVariabels;
	EnvironmentVariabelString.ParseIntoArray( EnvironmentVariabels, *FString( ";" ) );

	for( const FString& Variable: EnvironmentVariabels )
	{
		const FString Path = FPaths::Combine( Variable, InExecutableName );
		if( FPlatformFileManager::Get().GetPlatformFile().FileExists( *Path ) )
			return Path;
	}

	return "";
}