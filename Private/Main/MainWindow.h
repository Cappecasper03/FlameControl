// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FLAMECONTROL_API SMainWindow final : public SWindow
{
public:
	struct FTitleBarData
	{
		TSharedPtr< SWidget > Parent;
		TSharedPtr< SWidget > Content;
	};

	static void Run();

	static void OpenPopupWindow( const TSharedPtr< SWidget >& InContent );

	static void GetTitleBarContents( const TSharedRef< SWindow >& InWindow, FTitleBarData& OutLeftContent, FTitleBarData& OutCenterContent, FTitleBarData& OutRightContent );

private:
	static TSharedRef< SWindow > MakeWindow();

	static TSharedPtr< SWindow > MainWindow;
	static bool                  IsRunning;
};
