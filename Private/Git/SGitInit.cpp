// Fill out your copyright notice in the Description page of Project Settings.

#include "SGitInit.h"

#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "Main/SMainWindow.h"

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
				.OnReleased( this, &SGitInit::SelectFolder )
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
				.OnPressed_Lambda( []{ SMainWindow::ClosePopupWindow(); } )
			]

			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew( SButton )
				.Text( FText::FromString( "Cancel" ) )
				.OnPressed_Lambda( []{ SMainWindow::ClosePopupWindow(); } )
			]
		]
	];
	// clang-format on
}

void SGitInit::SelectFolder()
{
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if( !DesktopPlatform )
		return;

	FString SelectedFolder;
	if( DesktopPlatform->OpenDirectoryDialog( FSlateApplication::Get().FindBestParentWindowHandleForDialogs( nullptr ), "Select Folder", "", SelectedFolder ) )
		Folder->SetText( FText::FromString( SelectedFolder ) );
}
