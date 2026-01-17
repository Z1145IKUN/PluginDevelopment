// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Widget_ConfirmScreen.h"

#include "CommonTextBlock.h"
#include "Components/DynamicEntryBox.h"
#include "Widget/Component/GameUIButtonBase.h"

#define LOCTEXT_NAMESPACE "ConfrimScreen"

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateOkScreen(const FText& InScreenTitle,
                                                                   const FText& InScreenMessage)
{
	UConfirmScreenInfoObject* ConfirmScreenInfoObject = NewObject<UConfirmScreenInfoObject>();
	ConfirmScreenInfoObject->ConfirmScreenTitle = InScreenTitle;
	ConfirmScreenInfoObject->ConfirmScreenMessage = InScreenMessage;

	FConfirmScreenButtonInfo OKButtonInfo;
	OKButtonInfo.ButtonTextToDisplay = FText::FromString(LOCTEXT("OKButtonText", "OK").ToString());
	OKButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Closed;

	ConfirmScreenInfoObject->AvailableScreenButtons.Add(OKButtonInfo);

	return ConfirmScreenInfoObject;
}

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateYesNoScreen(const FText& InScreenTitle,
                                                                      const FText& InScreenMessage)
{
	UConfirmScreenInfoObject* ConfirmScreenInfoObject = NewObject<UConfirmScreenInfoObject>();
	ConfirmScreenInfoObject->ConfirmScreenTitle = InScreenTitle;
	ConfirmScreenInfoObject->ConfirmScreenMessage = InScreenMessage;

	FConfirmScreenButtonInfo YesButtonInfo;
	YesButtonInfo.ButtonTextToDisplay = FText::FromString(LOCTEXT("YesButtonText", "Yes").ToString());
	YesButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Confirmed;

	FConfirmScreenButtonInfo NoButtonInfo;
	NoButtonInfo.ButtonTextToDisplay = FText::FromString(LOCTEXT("NoButtonText", "No").ToString());
	NoButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Canceled;

	ConfirmScreenInfoObject->AvailableScreenButtons.Add(YesButtonInfo);
	ConfirmScreenInfoObject->AvailableScreenButtons.Add(NoButtonInfo);

	return ConfirmScreenInfoObject;
}

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateOkCancelScreen(const FText& InScreenTitle,
                                                                         const FText& InScreenMessage)
{
	UConfirmScreenInfoObject* ConfirmScreenInfoObject = NewObject<UConfirmScreenInfoObject>();
	ConfirmScreenInfoObject->ConfirmScreenTitle = InScreenTitle;
	ConfirmScreenInfoObject->ConfirmScreenMessage = InScreenMessage;

	FConfirmScreenButtonInfo ConfirmButtonInfo;
	ConfirmButtonInfo.ButtonTextToDisplay = FText::FromString(LOCTEXT("ConfirmButtonText", "Confirm").ToString());
	ConfirmButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Confirmed;

	FConfirmScreenButtonInfo CancelButtonInfo;
	CancelButtonInfo.ButtonTextToDisplay = FText::FromString(LOCTEXT("CancelButtonText", "Cancel").ToString());
	CancelButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Canceled;

	ConfirmScreenInfoObject->AvailableScreenButtons.Add(ConfirmButtonInfo);
	ConfirmScreenInfoObject->AvailableScreenButtons.Add(CancelButtonInfo);

	return ConfirmScreenInfoObject;
}

void UWidget_ConfirmScreen::InitConfirmScreen(UConfirmScreenInfoObject* InScreenInfoObject,
                                              TFunction<void(EConfirmScreenButtonType)> ClickedButtonCallBack)
{
	check(InScreenInfoObject && CommonTextBlock_Title && CommonTextBlock_Message && DynamicEntryBox_Buttons)

	CommonTextBlock_Title->SetText(InScreenInfoObject->ConfirmScreenTitle);
	CommonTextBlock_Message->SetText(InScreenInfoObject->ConfirmScreenMessage);

	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{
		DynamicEntryBox_Buttons->Reset<UGameUIButtonBase>(
			[](const UGameUIButtonBase& ExistingButton)
			{
				ExistingButton.OnClicked().Clear();
			}
		);
	}

	check(!InScreenInfoObject->AvailableScreenButtons.IsEmpty())

	for (const FConfirmScreenButtonInfo& ButtonInfo : InScreenInfoObject->AvailableScreenButtons)
	{
		UGameUIButtonBase* AddedButton = DynamicEntryBox_Buttons->CreateEntry<UGameUIButtonBase>();
		AddedButton->SetButtonText(ButtonInfo.ButtonTextToDisplay);
		AddedButton->OnClicked().AddLambda(
			[ClickedButtonCallBack,ButtonInfo,this]()
			{
				ClickedButtonCallBack(ButtonInfo.ConfirmScreenButtonType);
				DeactivateWidget();
			}
		);
	}
}

UWidget* UWidget_ConfirmScreen::NativeGetDesiredFocusTarget() const
{
	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{
		DynamicEntryBox_Buttons->GetAllEntries().Last()->SetFocus();
	}
	return Super::NativeGetDesiredFocusTarget();
}
#undef LOCTEXT_NAMESPACE
