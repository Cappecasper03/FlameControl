// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Application/SWindowTitleBar.h"

/**
 * 
 */
class FLAMECONTROL_API STitleBar final : public SWindowTitleBar
{
public:
	void Construct( const FArguments& InArgs, const TSharedRef< SWindow >& InWindow, const TSharedPtr< SWidget >& InCenterContent, EHorizontalAlignment InCenterContentAlignment );

protected:
	virtual void MakeTitleBarContentWidgets( TSharedPtr< SWidget >& OutLeftContent, TSharedPtr< SWidget >& OutRightContent ) override;
};
