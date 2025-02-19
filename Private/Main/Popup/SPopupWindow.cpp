// Fill out your copyright notice in the Description page of Project Settings.

#include "SPopupWindow.h"

#include "Main/SMainWindow.h"

void SPopupWindow::Construct( const FArguments& /*InArgs*/, const TSharedPtr< SWindow >& InWindow, const TSharedPtr< SWidget >& InContent )
{
	TSharedPtr< SWidget > LeftContent;
	TSharedPtr< SWidget > CenterContent;
	TSharedPtr< SWidget > RightContent;
	SMainWindow::GetTitleBarContents( InWindow.ToSharedRef(), LeftContent, CenterContent, RightContent );

	SHorizontalBox* LeftParent = reinterpret_cast< SHorizontalBox* >( LeftContent->GetParentWidget().Get() );
	LeftParent->RemoveSlot( LeftContent.ToSharedRef() );

	SOverlay* CenterParentParent = reinterpret_cast< SOverlay* >( CenterContent->GetParentWidget()->GetParentWidget().Get() );
	CenterParentParent->ClearChildren();

	// clang-format off
	ChildSlot
	[
		InContent.ToSharedRef()
	];
	// clang-format on
}