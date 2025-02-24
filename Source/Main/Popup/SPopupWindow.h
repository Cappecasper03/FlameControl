// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class FLAMECONTROL_API SPopupWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS( SPopupWindow ) {}
	SLATE_END_ARGS()

	void Construct( const FArguments& InArgs, const TSharedPtr< SWindow >& InWindow, const TSharedPtr< SWidget >& InContent );

	TSharedPtr<IWindowTitleBar> TitleBar;

};
