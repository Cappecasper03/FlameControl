// Fill out your copyright notice in the Description page of Project Settings.

#include "SGitClone.h"

#include "Main/FMainApp.h"

void SGitClone::Construct( const FArguments& /*InArgs*/ )
{
	// clang-format off
	ChildSlot
	[
		SNew( SVerticalBox )

		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew( STextBlock )
			.Text( FText::FromString( "Clone" ) )
		]

		+SVerticalBox::Slot()
		.FillHeight( 1 )
		[
			SNew( SGridPanel )
			.FillColumn( 1, 1 )

			+SGridPanel::Slot( 0, 0 )
			[
				SNew( STextBlock )
				.Text( FText::FromString(  "Remote URL:" ) )
			]
			+SGridPanel::Slot( 1, 0 )
			[
				SAssignNew( RemoteUrl, SEditableTextBox )
			]

			+SGridPanel::Slot( 0, 1 )
			[
				SNew( STextBlock )
				.Text( FText::FromString( "Parent Folder:" ) )
			]
			+SGridPanel::Slot( 1, 1 )
			[
				SAssignNew( Folder, SEditableTextBox )
				.Text( FText::FromString( "Default Folder" ) )
			]
			+SGridPanel::Slot( 2, 1 )
			[
				SNew( SButton )
				.Text( FText::FromString( "Select" ) )
				.OnReleased_Lambda( [ this ] { Folder->SetText( FText::FromString( FMainApp::OpenDirectoryDialog() ) ); } )
			]

			+SGridPanel::Slot( 0, 2 )
			[
				SNew( STextBlock )
				.Text( FText::FromString( "Name:" ) )
			]
			+SGridPanel::Slot( 1, 2 )
			[
				SAssignNew( Name, SEditableTextBox )
				.HintText( FText::FromString( "Optional" ) )
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
						const FString Command = "clone " + RemoteUrl->GetText().ToString() + " " + Name->GetText().ToString() + " --progress";
						FMainApp::ExecuteExecutableCommand( FMainApp::GetGitExecutablePath(), Command, Folder->GetText().ToString() );
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