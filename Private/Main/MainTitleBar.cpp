// Fill out your copyright notice in the Description page of Project Settings.

#include "MainTitleBar.h"

#include "Popup/PopupMenu.h"

void SMainTitleBar::Construct( const FArguments&            InArgs,
                               const TSharedRef< SWindow >& InWindow,
                               const TSharedPtr< SWidget >& InCenterContent,
                               const EHorizontalAlignment   InCenterContentAlignment )
{
	SWindowTitleBar::Construct( InArgs, InWindow, InCenterContent, InCenterContentAlignment );
}

void SMainTitleBar::MakeTitleBarContentWidgets( TSharedPtr< SWidget >& OutLeftContent, TSharedPtr< SWidget >& OutRightContent )
{
	SWindowTitleBar::MakeTitleBarContentWidgets( OutLeftContent, OutRightContent );

	OutLeftContent.Reset();

	// clang-format off
	TSharedPtr<SWidget> GitButton = SNew( SVerticalBox )
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew( SButton )
			.Text( FText::FromString( TEXT( "Clone" ) ) )
		]

		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew( SButton )
			.Text( FText::FromString( TEXT( "Init" ) ) )
		]
		
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew( SButton )
			.Text( FText::FromString( TEXT( "Open" ) ) )
		];

	TSharedPtr<SWidget> SvnButton = SNew( SVerticalBox )
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
	
	OutLeftContent = SNew( SHorizontalBox )
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
}
