// Fill out your copyright notice in the Description page of Project Settings.

#include "GitInit.h"

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
				SNew( SEditableTextBox )
				.Text( FText::FromString( "Default Folder" ) )
			]
		]
	];
	// clang-format on
}
