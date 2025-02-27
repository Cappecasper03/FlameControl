// Fill out your copyright notice in the Description page of Project Settings.

#include "SMainWindow.h"

#include "FMainApp.h"

TMap< FName, SMainWindow::FKeyBinding > SMainWindow::KeyBindings;
TSet< FKey >                            SMainWindow::PressedKeys;

void SMainWindow::AddKeyBinding( const FName& Name, const TSet< FKey >& ActivationKeys, const FSimpleDelegate& OnActivation, const TWeakPtr< SWindow >& Owner )
{
	if( !OnActivation.IsBound() )
		return;

	KeyBindings.Add( Name, FKeyBinding{ ActivationKeys, OnActivation, Owner } );
}

FReply SMainWindow::OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent )
{
	PressedKeys.Add( InKeyEvent.GetKey() );

	CheckKeyBindingActivations();

	return SWindow::OnKeyDown( MyGeometry, InKeyEvent );
}

FReply SMainWindow::OnKeyUp( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent )
{
	PressedKeys.Remove( InKeyEvent.GetKey() );

	return SWindow::OnKeyUp( MyGeometry, InKeyEvent );
}

void SMainWindow::CheckKeyBindingActivations()
{
	TArray< FKeyBinding > Array;
	KeyBindings.GenerateValueArray( Array );

	for( const FKeyBinding& KeyBind: Array )
	{
		bool ShouldActivate = true;
		for( const FKey& Key: KeyBind.ActivationKeys )
		{
			if( !PressedKeys.Contains( Key ) )
			{
				ShouldActivate = false;
				break;
			}
		}

		if( !ShouldActivate )
			continue;

		if( !KeyBind.Owner.IsValid() )
		{
			KeyBind.OnActivation.Execute();
			continue;
		}

		const SWindow* Owner = KeyBind.Owner.Pin().Get();
		if( FMainApp::GetMainWindow().HasSameObject( Owner ) || FMainApp::GetPopupWindow().HasSameObject( Owner ) )
			KeyBind.OnActivation.Execute();
	}
}