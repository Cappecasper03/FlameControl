// Fill out your copyright notice in the Description page of Project Settings.

#include "PopupMenu.h"

void SPopupMenu::Construct( const FArguments& InArgs, const TSharedPtr< SWidget >& Content )
{
	// clang-format off
	ChildSlot
	[
		SAssignNew( MenuAnchor, SMenuAnchor )
		.MenuContent( Content )
		[
			SNew( SButton )
			.Text( InArgs._Text )
			.OnPressed( this, &SPopupMenu::OnButtonPressed )
		]
	];
	// clang-format on
}

void SPopupMenu::OnButtonPressed()
{
	MenuAnchor->SetIsOpen( MenuAnchor->ShouldOpenDueToClick() );
}
