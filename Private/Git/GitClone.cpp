// Fill out your copyright notice in the Description page of Project Settings.

#include "GitClone.h"

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
				SNew( SEditableTextBox )
			]

			+SGridPanel::Slot( 0, 1 )
			[
				SNew( STextBlock )
				.Text( FText::FromString( "Parent Folder:" ) )
			]
			+SGridPanel::Slot( 1, 1 )
			[
				SNew( SEditableTextBox )
				.Text( FText::FromString( "Default Folder" ) )
			]

			+SGridPanel::Slot( 0, 1 )
			[
				SNew( STextBlock )
				.Text( FText::FromString( "Name:" ) )
			]
			+SGridPanel::Slot( 1, 1 )
			[
				SNew( SEditableTextBox )
				.HintText( FText::FromString( "Optional" ) )
			]
		]
	];
	// clang-format on
}