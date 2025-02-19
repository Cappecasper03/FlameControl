// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class FLAMECONTROL_API SGitClone : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS( SGitClone ) {}
	SLATE_END_ARGS()

	void Construct( const FArguments& InArgs );
};
