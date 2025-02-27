// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
class FLAMECONTROL_API SMainWindow final : public SWindow
{
public:
	static void AddKeyBinding( const FName& Name, const TSet< FKey >& ActivationKeys, const FSimpleDelegate& OnActivation, const TWeakPtr< SWindow >& Owner );
	static void RemoveKeyBinding( const FName& Name ) { KeyBindings.Remove( Name ); }

private:
	struct FKeyBinding
	{
		TSet< FKey >        ActivationKeys;
		FSimpleDelegate     OnActivation;
		TWeakPtr< SWindow > Owner;
	};

	virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;
	virtual FReply OnKeyUp( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;

	static void CheckKeyBindingActivations();

	static TMap< FName, FKeyBinding > KeyBindings;
	static TSet< FKey >               PressedKeys;
};
