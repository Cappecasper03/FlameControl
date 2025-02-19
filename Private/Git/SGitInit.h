// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class FLAMECONTROL_API SGitInit final : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS( SGitInit ) {}
	SLATE_END_ARGS()

	void Construct( const FArguments& InArgs );

private:
	void SelectFolder();

	TSharedPtr< SEditableTextBox > Folder;
};
