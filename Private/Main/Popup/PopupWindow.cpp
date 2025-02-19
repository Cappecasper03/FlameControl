// Fill out your copyright notice in the Description page of Project Settings.

#include "PopupWindow.h"

#include "Main/MainWindow.h"

void SPopupWindow::Construct( const FArguments& /*InArgs*/, const TSharedRef< SWindow >& InWindow, const TSharedPtr< SWidget >& InContent )
{
	SMainWindow::FTitleBarData LeftContent;
	SMainWindow::FTitleBarData CenterContent;
	SMainWindow::FTitleBarData RightContent;
	SMainWindow::GetTitleBarContents( InWindow, LeftContent, CenterContent, RightContent );

	SHorizontalBox* LeftParent = reinterpret_cast< SHorizontalBox* >( LeftContent.Parent.Get() );
	LeftParent->RemoveSlot( LeftContent.Content->GetParentWidget().ToSharedRef() );

	SHorizontalBox* CenterParent = reinterpret_cast< SHorizontalBox* >( CenterContent.Parent.Get() );
	CenterParent->RemoveSlot( CenterContent.Content->GetParentWidget().ToSharedRef() );

	// clang-format off
	ChildSlot
	[
		InContent.ToSharedRef()
	];
	// clang-format on
}