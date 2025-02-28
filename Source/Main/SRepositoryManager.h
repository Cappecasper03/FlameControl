// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 *
 */
class FLAMECONTROL_API SRepositoryManager : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS( SRepositoryManager ) {}
	SLATE_END_ARGS()

	void Construct( const FArguments& InArgs );
};
