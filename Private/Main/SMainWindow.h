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

	static void OpenPopupWindow( const TSharedPtr< SWidget >& InContent );
	static void ClosePopupWindow();

	static void GetTitleBarContents( const TSharedRef< SWindow >& InWindow,
	                                 TSharedPtr< SWidget >&       OutLeftContent,
	                                 TSharedPtr< SWidget >&       OutCenterContent,
	                                 TSharedPtr< SWidget >&       OutRightContent );

private:
	static TSharedRef< SWindow > MakeWindow();

	static TSharedPtr< SWindow > MainWindow;
	static TSharedPtr< SWindow > PopupWindow;
	static bool                  IsRunning;
};
