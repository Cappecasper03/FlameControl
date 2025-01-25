// Fill out your copyright notice in the Description page of Project Settings.

#include "TitleBar.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void STitleBar::Construct( const FArguments&            InArgs,
                           const TSharedRef< SWindow >& InWindow,
                           const TSharedPtr< SWidget >& InCenterContent,
                           const EHorizontalAlignment   InCenterContentAlignment )
{
	SWindowTitleBar::Construct( InArgs, InWindow, InCenterContent, InCenterContentAlignment );
}
void STitleBar::MakeTitleBarContentWidgets( TSharedPtr< SWidget >& OutLeftContent, TSharedPtr< SWidget >& OutRightContent )
{
	SWindowTitleBar::MakeTitleBarContentWidgets( OutLeftContent, OutRightContent );

	OutLeftContent = SNew( SImage );
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
