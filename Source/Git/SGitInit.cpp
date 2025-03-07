﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "SGitInit.h"

#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "Main/FMainApp.h"

void SGitInit::Construct( const FArguments& /*InArgs*/ )
{
	// clang-format off
	ChildSlot
	[
		SNew( SVerticalBox )

		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew( STextBlock )
			.Text( FText::FromString( "Init" ) )
		]

		+SVerticalBox::Slot()
		.FillHeight( 1 )
		[
			SNew( SGridPanel )
			.FillColumn( 1, 1 )

			+SGridPanel::Slot( 0, 0 )
			[
				SNew( STextBlock )
				.Text( FText::FromString( "Folder:" ) )
			]
			+SGridPanel::Slot( 1, 0 )
			[
				SAssignNew( Folder, SEditableTextBox )
				.Text( FText::FromString( "Default Folder" ) )
			]
			+SGridPanel::Slot( 2, 0 )
			[
				SNew( SButton )
				.Text( FText::FromString( "Select" ) )
				.OnReleased_Lambda( [ this ] { Folder->SetText( FText::FromString( FMainApp::OpenDirectoryDialog() ) ); } )
			]
		]

		+SVerticalBox::Slot()
		.AutoHeight()
		.HAlign( HAlign_Right )
		[
			SNew( SHorizontalBox )

			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew( SButton )
				.Text( FText::FromString( "Ok" ) )
				.OnPressed_Lambda(
					[ this ]
					{
						FMainApp::ExecuteExecutableCommand( FMainApp::GetGitExecutablePath(), "init", Folder->GetText().ToString() );
						FMainApp::ClosePopupWindow();
					} )
			]

			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew( SButton )
				.Text( FText::FromString( "Cancel" ) )
				.OnPressed_Lambda( []{ FMainApp::ClosePopupWindow(); } )
			]
		]
	];
	// clang-format on
}