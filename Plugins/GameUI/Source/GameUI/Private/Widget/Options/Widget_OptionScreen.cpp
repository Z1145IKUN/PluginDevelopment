// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/Widget_OptionScreen.h"

#include "ICommonInputModule.h"
#include "Input/CommonUIInputTypes.h"

void UWidget_OptionScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!ResetAction.IsNull())
	{
		ResetAction_Handle = RegisterUIActionBinding(
			FBindUIActionArgs(
				ResetAction,
				true,
				FSimpleDelegate::CreateUObject(
					this,
					&ThisClass::OnResetActionTriggered
				)
			)
		);
	}

	RegisterUIActionBinding(
		FBindUIActionArgs(
			ICommonInputModule::GetSettings().GetDefaultBackAction(),
			true,
			FSimpleDelegate::CreateUObject(
				this,
				&ThisClass::OnBackActionTriggered
			)
		)
	);
}

void UWidget_OptionScreen::OnResetActionTriggered()
{
}

void UWidget_OptionScreen::OnBackActionTriggered()
{
	DeactivateWidget();
}
