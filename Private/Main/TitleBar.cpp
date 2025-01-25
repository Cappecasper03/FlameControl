// Fill out your copyright notice in the Description page of Project Settings.

#include "TitleBar.h"

#include "SlateOptMacros.h"
#include "WindowControl.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void STitleBar::Construct( const FArguments& InArgs )
{
	// clang-format off
	ChildSlot
	[
		SNew( SHorizontalBox )

		// Menus
		+ SHorizontalBox::Slot()
		[
			SNew( SHorizontalBox )

			+ SHorizontalBox::Slot()
			[
				SNew( SHorizontalBox )

				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew( SButton )
					.Text( FText::FromString( "Git" ) )
				]

				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew( SButton )
					.Text( FText::FromString( "Svn" ) )
				]
			]
		]

		// Logo/Name & Command Logs
		+ SHorizontalBox::Slot()
		.HAlign( HAlign_Center )
		.VAlign( VAlign_Center )
		[
			SNew( STextBlock )
			.Text( FText::FromString( "FlameControl" ) )
			.Justification( ETextJustify::Center )
		]

		// Window Control
		+ SHorizontalBox::Slot()
		[
			SNew( SWindowControl)
		]
	];
	// clang-format on
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
