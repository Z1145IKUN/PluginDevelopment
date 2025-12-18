// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Component/GameUIButtonBase.h"

#include "CommonTextBlock.h"

void UGameUIButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetButtonText(ButtonDisplayText);
}

void UGameUIButtonBase::SetButtonText(FText InButtonText)
{
	if (CommonTextBlock_ButtonText && !InButtonText.IsEmpty())
	{
		CommonTextBlock_ButtonText->SetText(bUseUpperCaseForButtonText ? InButtonText.ToUpper() : InButtonText);
	}
}
