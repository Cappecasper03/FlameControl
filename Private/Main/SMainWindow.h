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

	static void ExecuteProcessCommand( const FString& InExecutablePath, const FString& InCommand, const FString& InWorkingDirectory );

	static const FString& GetGitExecutablePath() { return GitExecutablePath; }

private:
	static TSharedRef< SWindow > MakeWindow();

	static FString GetExecutablePath( const FString& InExecutableName );

	static TSharedPtr< SWindow > MainWindow;
	static TSharedPtr< SWindow > PopupWindow;
	static bool                  IsRunning;

	static FString GitExecutablePath;
};
