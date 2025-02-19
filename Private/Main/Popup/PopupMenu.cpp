// Fill out your copyright notice in the Description page of Project Settings.

#include "PopupMenu.h"

void SPopupMenu::Construct( const FArguments& InArgs, const TSharedPtr< SWidget >& InContent )
{
	// clang-format off
	ChildSlot
	[
		SAssignNew( MenuAnchor, SMenuAnchor )
		.MenuContent( InContent )
		[
			SNew( SButton )
			.Text( InArgs._Text )
			.OnPressed( this, &SPopupMenu::OnButtonPressed )
		]
	];
	// clang-format on
}

void SPopupMenu::OnButtonPressed() const
{
	MenuAnchor->SetIsOpen( MenuAnchor->ShouldOpenDueToClick() );
}
