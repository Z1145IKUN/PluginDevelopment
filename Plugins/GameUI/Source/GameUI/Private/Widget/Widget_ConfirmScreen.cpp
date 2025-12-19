// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Widget_ConfirmScreen.h"

#include "CommonTextBlock.h"
#include "ICommonInputModule.h"
#include "Components/DynamicEntryBox.h"
#include "Widget/Component/GameUIButtonBase.h"

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateOkScreen(const FText& InScreenTitle,
                                                                   const FText& InScreenMessage)
{
	UConfirmScreenInfoObject* ConfirmScreenInfoObject = NewObject<UConfirmScreenInfoObject>();
	ConfirmScreenInfoObject->ConfirmScreenTitle = InScreenTitle;
	ConfirmScreenInfoObject->ConfirmScreenMessage = InScreenMessage;

	FConfirmScreenButtonInfo OKButtonInfo;
	OKButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("OK"));
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
	YesButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Yes"));
	YesButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Confirmed;

	FConfirmScreenButtonInfo NoButtonInfo;
	NoButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("No"));
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

	FConfirmScreenButtonInfo OkButtonInfo;
	OkButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Ok"));
	OkButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Confirmed;

	FConfirmScreenButtonInfo CancelButtonInfo;
	CancelButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Cancel"));
	CancelButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Canceled;

	ConfirmScreenInfoObject->AvailableScreenButtons.Add(OkButtonInfo);
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
			[](UGameUIButtonBase& ExistingButton)
			{
				ExistingButton.OnClicked().Clear();
			}
		);
	}

	check(!InScreenInfoObject->AvailableScreenButtons.IsEmpty())

	for (const FConfirmScreenButtonInfo& ButtonInfo : InScreenInfoObject->AvailableScreenButtons)
	{
		FDataTableRowHandle InputActionRowHandle;
		switch (ButtonInfo.ConfirmScreenButtonType)
		{
		case EConfirmScreenButtonType::Confirmed:
			InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultClickAction();
			break;
		case EConfirmScreenButtonType::Canceled:
			InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();
			break;
		case EConfirmScreenButtonType::Closed:
			InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();
			break;
		default:
			break;
		}

		UGameUIButtonBase* AddedButton = DynamicEntryBox_Buttons->CreateEntry<UGameUIButtonBase>();
		AddedButton->SetButtonText(ButtonInfo.ButtonTextToDisplay);
		AddedButton->SetTriggeringInputAction(InputActionRowHandle); 
		AddedButton->OnClicked().AddLambda(
			[ClickedButtonCallBack,ButtonInfo,this]()
			{
				ClickedButtonCallBack(ButtonInfo.ConfirmScreenButtonType);
				DeactivateWidget();
			}
		);
	}

	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{
		DynamicEntryBox_Buttons->GetAllEntries().Last()->SetFocus();
	}
}
