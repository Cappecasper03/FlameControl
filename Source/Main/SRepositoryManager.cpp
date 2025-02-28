// Fill out your copyright notice in the Description page of Project Settings.

#include "SRepositoryManager.h"

void SRepositoryManager::Construct( const FArguments& InArgs )
{
	// clang-format off
	ChildSlot
	[
		SNew( SSplitter )
		.Orientation( Orient_Horizontal )

		+SSplitter::Slot()
		.Value( .15f )
		[
			SNew( SVerticalBox )

			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew( STextBlock )
				.Text( FText::FromString( "Repository Manager" ) )
				.Justification( ETextJustify::Center )
			]

			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew( SVerticalBox )

				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew( STextBlock )
					.Text( FText::FromString( "Recent" ) )
				]
			]

			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew( SVerticalBox )

				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew( STextBlock )
					.Text( FText::FromString( "Git" ) )
				]
			]

			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew( SVerticalBox )

				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew( STextBlock )
					.Text( FText::FromString( "Svn" ) )
				]
			]
		]

		+SSplitter::Slot()
		.Value( .85f )
		[
			SNew( SImage )
		]
	];
	// clang-format on
}
