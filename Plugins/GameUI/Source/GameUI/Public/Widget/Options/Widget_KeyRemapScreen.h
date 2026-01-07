// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonInputTypeEnum.h"
#include "Framework/Application/IInputProcessor.h"
#include "Widget/Widget_ActivatableBase.h"
#include "Widget_KeyRemapScreen.generated.h"

class UCommonRichTextBlock;
class FKeyRemapScreenInputPreprocessor;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta=(DisableNativeTick))
class GAMEUI_API UWidget_KeyRemapScreen : public UWidget_ActivatableBase
{
	GENERATED_BODY()

public:
	DECLARE_DELEGATE_OneParam(FOnKeyRemapScreenKeyPressedDelegate, const FKey& /*PressedKey*/);
	FOnKeyRemapScreenKeyPressedDelegate OnKeyRemapScreenKeyPressed;

	DECLARE_DELEGATE_OneParam(FOnKeyRemapScreenKeySelectedCanceledDelegate, const FString& /*CanceledReason*/);
	FOnKeyRemapScreenKeySelectedCanceledDelegate OnKeyRemapScreenKeySelectedCanceled;

	void SetDesiredInputTypeToFilter(ECommonInputType InDesiredInputType);

protected:
	//~ Begin UCommonActivatableWidget interface
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	//~ End UCommonActivatableWidget interface

private:
	void OnValidKeyPressedDetected(const FKey& PressedKey);
	void OnKeySelectedCanceled(const FString& CanceledReason);

	/**
	 * Delay a tick to make sure the input key is captured properly before calling the PreDeactivateCallback
	 * and deactivating the widget
	 */
	void RequestDeactivationWidget(TFunction<void()> PreDeactivateCallback);

	//***** Bound Widget *****//
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonRichTextBlock> CommonRichTextBlock_RemapMassage;
	//***** Bound Widget *****//

	TSharedPtr<FKeyRemapScreenInputPreprocessor> InputPreprocessor;

	ECommonInputType DesiredInputType;
};


/**
 * 预处理程序
 */
class FKeyRemapScreenInputPreprocessor : public IInputProcessor
{
public:
	FKeyRemapScreenInputPreprocessor(ECommonInputType InInputTypeToListenTo);

	DECLARE_DELEGATE_OneParam(FOnInputPreprocessorKeyPressedDelegate, const FKey& /*PressedKey*/);
	FOnInputPreprocessorKeyPressedDelegate OnInputPreprocessorKeyPressed;

	DECLARE_DELEGATE_OneParam(FOnInputPreprocessorKeyPressedCanceledDelegate, const FString& /*CanceledReason*/);
	FOnInputPreprocessorKeyPressedCanceledDelegate OnInputPreprocessorKeyPressedCanceled;

protected:
	// ~ Begin IInputProcessor interface
	virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override;
	virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;
	virtual bool HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;
	// ~ End IInputProcessor interface

	void ProcessPressedKey(const FKey& InPressedKey);

private:
	ECommonInputType InputTypeToListenTo;
};
