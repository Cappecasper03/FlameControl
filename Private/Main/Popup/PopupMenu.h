// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class FLAMECONTROL_API SPopupMenu final : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS( SPopupMenu )
		: _Text()
	{}

	SLATE_ATTRIBUTE( FText, Text )

	SLATE_END_ARGS()

	void Construct( const FArguments& InArgs, const TSharedPtr< SWidget >& Content );

private:
	void OnButtonPressed();

	TSharedPtr< SMenuAnchor > MenuAnchor;
};
