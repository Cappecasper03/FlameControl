// Fill out your copyright notice in the Description page of Project Settings.

#include "MainTitleBar.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

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

	// clang-format off
	OutLeftContent = SNew( SHorizontalBox )
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew( SButton ).Text( FText::FromString( "Git" ) )
		]

		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew( SButton ).Text( FText::FromString( "Svn" ) )
		];
	// clang-format on
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
