// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FLAMECONTROL_API SMainWindow final : public SWindow
{
public:
	static void Run();

private:
	static TSharedRef< SWindow > MakeWindow();

	static bool IsRunning;
};
