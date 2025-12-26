// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Component/GameUIButtonBase.h"

#include "CommonTextBlock.h"
#include "Subsystem/GameUISubsystem.h"

void UGameUIButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetButtonText(ButtonDisplayText);
}

void UGameUIButtonBase::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();

	if (CommonTextBlock_ButtonText && GetCurrentTextStyleClass())
	{
		CommonTextBlock_ButtonText->SetStyle(GetCurrentTextStyleClass());
	}
}

void UGameUIButtonBase::NativeOnHovered()
{
	Super::NativeOnHovered();

	if (!ButtonDescriptionText.IsEmpty())
	{
		UGameUISubsystem::Get(this)->OnDescriptionTextUpdate.Broadcast(this, ButtonDescriptionText);
	}
}

void UGameUIButtonBase::NativeOnUnhovered()
{
	Super::NativeOnUnhovered();

	UGameUISubsystem::Get(this)->OnDescriptionTextUpdate.Broadcast(this, FText::GetEmpty());
}

void UGameUIButtonBase::SetButtonText(FText InButtonText)
{
	if (CommonTextBlock_ButtonText && !InButtonText.IsEmpty())
	{
		CommonTextBlock_ButtonText->SetText(bUseUpperCaseForButtonText ? InButtonText.ToUpper() : InButtonText);
	}
}

FText UGameUIButtonBase::GetButtonDisplayText() const
{
	if (CommonTextBlock_ButtonText)
	{
		return CommonTextBlock_ButtonText->GetText();
	}

	return FText();
}
