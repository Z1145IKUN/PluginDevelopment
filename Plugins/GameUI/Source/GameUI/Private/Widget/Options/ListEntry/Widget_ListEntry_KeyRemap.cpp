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
