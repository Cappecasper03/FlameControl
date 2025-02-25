// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FLAMECONTROL_API FMainApp
{
public:
	static void OpenPopupWindow( const TSharedPtr< SWidget >& InContent );
	static void ClosePopupWindow();

	static void GetTitleBarContents( const TSharedRef< SWindow >& InWindow,
	                                 TSharedPtr< SWidget >&       OutLeftContent,
	                                 TSharedPtr< SWidget >&       OutCenterContent,
	                                 TSharedPtr< SWidget >&       OutRightContent );

	static void ExecuteExecutableCommand( const FString& InExecutablePath, const FString& InCommand, const FString& InWorkingDirectory );

	static FString OpenDirectoryDialog();

	static const FString& GetGitExecutablePath() { return GitExecutablePath; }

	static TSharedRef< SWindow > MakeWindow();

private:
	static FString GetExecutablePath( const FString& InExecutableName );

	static TWeakPtr< SWindow > MainWindow;
	static TWeakPtr< SWindow > PopupWindow;

	static FString GitExecutablePath;
};
