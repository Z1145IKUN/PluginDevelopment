// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/Widget_KeyRemapScreen.h"

#include "CommonInputSubsystem.h"
#include "CommonRichTextBlock.h"
#include "CommonUITypes.h"
#include "ICommonInputModule.h"

void UWidget_KeyRemapScreen::SetDesiredInputTypeToFilter(ECommonInputType InDesiredInputType)
{
	DesiredInputType = InDesiredInputType;
}

void UWidget_KeyRemapScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	InputPreprocessor = MakeShared<FKeyRemapScreenInputPreprocessor>(DesiredInputType, GetOwningLocalPlayer());
	InputPreprocessor->OnInputPreprocessorKeyPressed.BindUObject(this, &ThisClass::OnValidKeyPressedDetected);
	InputPreprocessor->OnInputPreprocessorKeyPressedCanceled.BindUObject(this, &ThisClass::OnKeySelectedCanceled);

	FSlateApplication::Get().RegisterInputPreProcessor(InputPreprocessor, -1);

	FString InputDeviceName;
	switch (DesiredInputType)
	{
	case ECommonInputType::MouseAndKeyboard:
		InputDeviceName = TEXT("Mouse & Keyboard");
		break;
	case ECommonInputType::Gamepad:
		InputDeviceName = TEXT("Gamepad");
		break;
	default:
		break;
	}

	const FString DisplayRichMessage = FString::Printf(
		TEXT("<KeyRemapDefault>Press Any</> <KeyRemapHighlight>%s</> <KeyRemapDefault>Key.</>"), *InputDeviceName
	);

	CommonRichTextBlock_RemapMassage->SetText(FText::FromString(DisplayRichMessage));
}

void UWidget_KeyRemapScreen::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	if (InputPreprocessor)
	{
		FSlateApplication::Get().UnregisterInputPreProcessor(InputPreprocessor);

		InputPreprocessor.Reset();
	}
}

void UWidget_KeyRemapScreen::OnValidKeyPressedDetected(const FKey& PressedKey)
{
	RequestDeactivationWidget(
		[this,PressedKey]()
		{
			OnKeyRemapScreenKeyPressed.ExecuteIfBound(PressedKey);
		}
	);
}

void UWidget_KeyRemapScreen::OnKeySelectedCanceled(const FString& CanceledReason)
{
	RequestDeactivationWidget(
		[this,CanceledReason]()
		{
			OnKeyRemapScreenKeySelectedCanceled.ExecuteIfBound(CanceledReason);
		}
	);
}

void UWidget_KeyRemapScreen::RequestDeactivationWidget(TFunction<void()> PreDeactivateCallback)
{
	//delay a tick to make sure the input is processed correctly
	FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateLambda(
			[PreDeactivateCallback,this](float DeltaTime)
			{
				PreDeactivateCallback();
				DeactivateWidget();
				return false;
			}
		)
	);
}

//********** FKeyRemapScreenInputPreprocessor **********//
FKeyRemapScreenInputPreprocessor::FKeyRemapScreenInputPreprocessor(
	ECommonInputType InInputTypeToListenTo,
	ULocalPlayer* InOwningLocalPlayer)
{
	InputTypeToListenTo = InInputTypeToListenTo;
	CachedWeakLocalPlayer = InOwningLocalPlayer;
}

void FKeyRemapScreenInputPreprocessor::Tick(
	const float DeltaTime,
	FSlateApplication& SlateApp,
	TSharedRef<ICursor> Cursor)
{
}

bool FKeyRemapScreenInputPreprocessor::HandleKeyDownEvent(
	FSlateApplication& SlateApp,
	const FKeyEvent& InKeyEvent)
{
	ProcessPressedKey(InKeyEvent.GetKey());
	return true;
}

bool FKeyRemapScreenInputPreprocessor::HandleMouseButtonDownEvent(
	FSlateApplication& SlateApp,
	const FPointerEvent& MouseEvent)
{
	ProcessPressedKey(MouseEvent.GetEffectingButton());
	return true;
}

void FKeyRemapScreenInputPreprocessor::ProcessPressedKey(const FKey& InPressedKey)
{
	if (InPressedKey == EKeys::Escape)
	{
		OnInputPreprocessorKeyPressedCanceled.ExecuteIfBound(TEXT("Key Remap has been canceled"));
		return;
	}

	UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(CachedWeakLocalPlayer.Get());
	check(CommonInputSubsystem);
	ECommonInputType CurrentInputType = CommonInputSubsystem->GetCurrentInputType();

	switch (InputTypeToListenTo)
	{
	case ECommonInputType::MouseAndKeyboard:
		if (InPressedKey.IsGamepadKey() || CurrentInputType == ECommonInputType::Gamepad)
		{
			OnInputPreprocessorKeyPressedCanceled.ExecuteIfBound(
				TEXT("Detected gamepad key presses for keyboard inputs,Key Remap has been canceled"));
			return;
		}
		break;
	case ECommonInputType::Gamepad:
		if (CurrentInputType == ECommonInputType::Gamepad && InPressedKey == EKeys::LeftMouseButton)
		{
			FCommonInputActionDataBase* InputActionData = ICommonInputModule::GetSettings().GetDefaultClickAction().
				GetRow<FCommonInputActionDataBase>(TEXT(""));

			check(InputActionData);
			OnInputPreprocessorKeyPressed.ExecuteIfBound(InputActionData->GetDefaultGamepadInputTypeInfo().GetKey());

			return;
		}

		if (!InPressedKey.IsGamepadKey())
		{
			OnInputPreprocessorKeyPressedCanceled.ExecuteIfBound(
				TEXT("Detected non gamepad key presses for keyboard inputs,Key Remap has been canceled"));
			return;
		}
		break;
	default:
		break;
	}

	OnInputPreprocessorKeyPressed.ExecuteIfBound(InPressedKey);
}
