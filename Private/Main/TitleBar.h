﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class FLAMECONTROL_API STitleBar : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS( STitleBar ) {}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct( const FArguments& InArgs );

private:
	virtual EWindowZone::Type GetWindowZoneOverride() const override { return EWindowZone::TitleBar; }
};
