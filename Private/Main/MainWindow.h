// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FLAMECONTROL_API SMainWindow final : public SWindow
{
public:
	SMainWindow();
	virtual ~SMainWindow() override;

	static void Run();

private:
	static TSharedRef< SWindow > CreateWindow();

	static bool IsRunning;
};
