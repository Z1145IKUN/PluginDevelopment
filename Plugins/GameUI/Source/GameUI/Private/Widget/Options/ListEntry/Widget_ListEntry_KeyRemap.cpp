// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/ListEntry/Widget_ListEntry_KeyRemap.h"

#include "GameUIGameplayTags.h"
#include "FunctionLibrary/GameUIFunctionLibrary.h"
#include "Subsystem/GameUISubsystem.h"
#include "Widget/Component/GameUIButtonBase.h"
#include "Widget/Options/Widget_KeyRemapScreen.h"
#include "Widget/Options/DataObject/ListDataObject_KeyRemap.h"

void UWidget_ListEntry_KeyRemap::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CommonButton_RemapKey->OnClicked().AddUObject(this, &ThisClass::OnRemapKeyButtonClicked);
	CommonButton_ResetKeyBinding->OnClicked().AddUObject(this, &ThisClass::OnResetKeyBindingButtonClicked);
}

void UWidget_ListEntry_KeyRemap::OnListDataObjectSet(UListDataObject_Base* InListDataObject)
{
	Super::OnListDataObjectSet(InListDataObject);

	KeyRemapListDataObject = CastChecked<UListDataObject_KeyRemap>(InListDataObject);

	CommonButton_RemapKey->SetButtonImage(KeyRemapListDataObject->GetIconFromCurrentKey());
}

void UWidget_ListEntry_KeyRemap::OnListDataObjectModified(UListDataObject_Base* ModifiedData,
                                                          EOptionsListDataModifyReason ModifyReason)
{
	if (KeyRemapListDataObject)
	{
		CommonButton_RemapKey->SetButtonImage(KeyRemapListDataObject->GetIconFromCurrentKey());
	}
}

void UWidget_ListEntry_KeyRemap::OnRemapKeyButtonClicked()
{
	SelectedThisEntryWidget();

	UGameUISubsystem::Get(this)->PushSoftWidgetToStack(
		GameUIGameplayTags::GameUI_WidgetStack_Modal,
		UGameUIFunctionLibrary::GetSoftWidgetClassByTag(GameUIGameplayTags::GameUI_Widget_KeyRemapScreen),
		[this](EAsyncPushWidgetState PushWidgetState, UWidget_ActivatableBase* PushWidget)
		{
			if (PushWidgetState == EAsyncPushWidgetState::OnCreatedBeforePush)
			{
				UWidget_KeyRemapScreen* CreatedKeyRemapScreen = CastChecked<UWidget_KeyRemapScreen>(PushWidget);

				CreatedKeyRemapScreen->OnKeyRemapScreenKeyPressed.BindUObject(this, &ThisClass::OnKeyRemapPressed);
				CreatedKeyRemapScreen->OnKeyRemapScreenKeySelectedCanceled.BindUObject(
					this, &ThisClass::OnKeyRemapCanceled);

				if (KeyRemapListDataObject)
				{
					CreatedKeyRemapScreen->SetDesiredInputTypeToFilter(KeyRemapListDataObject->GetDesiredInputType());
				}
			}
		}
	);
}

void UWidget_ListEntry_KeyRemap::OnResetKeyBindingButtonClicked()
{
	SelectedThisEntryWidget();

	check(KeyRemapListDataObject);
	/**
	 *	check if the current key is already the default key 
	 *	if yes,display ok screen that says this is already the default key to player
	 *	if no,reset the key binding back to default
	 */
	if (!KeyRemapListDataObject->CanResetBackToDefaultValue())
	{
		UGameUISubsystem::Get(this)->PushConfirmScreenToModalStackAsync(
			EConfirmScreenType::OK,
			FText::FromString(TEXT("Reset Key Remap")),
			FText::FromString(TEXT("The key binding for ")
				+ KeyRemapListDataObject->GetDataDisplayName().ToString()
				+ TEXT(" is already set to default")),
			[](EConfirmScreenButtonType ClickedButton)
			{
			}
		);
	}
	else
	{
		UGameUISubsystem::Get(this)->PushConfirmScreenToModalStackAsync(
			EConfirmScreenType::YesNo,
			FText::FromString(TEXT("Reset Key Remap")),
			FText::FromString(TEXT("Do you want to reset the key binding for ")
				+ KeyRemapListDataObject->GetDataDisplayName().ToString()
				+ TEXT(" ?")),
			[this](EConfirmScreenButtonType ClickedButton)
			{
				if (ClickedButton == EConfirmScreenButtonType::Confirmed)
				{
					KeyRemapListDataObject->TryResetBackToDefaultValue();
				}
			}
		);
	}
}

void UWidget_ListEntry_KeyRemap::OnKeyRemapPressed(const FKey& PressedKey)
{
	if (KeyRemapListDataObject)
	{
		KeyRemapListDataObject->BindNewInputKey(PressedKey);
	}
}

void UWidget_ListEntry_KeyRemap::OnKeyRemapCanceled(const FString& CanceledReason)
{
	UGameUISubsystem::Get(this)->PushConfirmScreenToModalStackAsync(
		EConfirmScreenType::OK,
		FText::FromString(TEXT("Key Remap")),
		FText::FromString(CanceledReason),
		[](EConfirmScreenButtonType ClickedButton)
		{
		}
	);
}
