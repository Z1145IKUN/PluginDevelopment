// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/ListEntry/Widget_ListEntry_Base.h"

#include "CommonInputSubsystem.h"
#include "CommonTextBlock.h"
#include "Widget/Component/GameUIListView.h"
#include "Widget/Options/DataObject/ListDataObject_Base.h"

void UWidget_ListEntry_Base::NativeOnListEntryWidgetHovered(bool bWasHovered)
{
	BP_OnListEntryWidgetHovered(bWasHovered, IsListItemSelected());
}

void UWidget_ListEntry_Base::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	OnListDataObjectSet(CastChecked<UListDataObject_Base>(ListItemObject));

	SetVisibility(ESlateVisibility::Visible);
}

void UWidget_ListEntry_Base::OnListDataObjectSet(UListDataObject_Base* InListDataObject)
{
	if (CommonTextBlock_SettingDisplayName)
	{
		CommonTextBlock_SettingDisplayName->SetText(InListDataObject->GetDataDisplayName());
	}

	if (!InListDataObject->OnListDataModified.IsBoundToObject(this))
	{
		InListDataObject->OnListDataModified.AddUObject(this, &ThisClass::OnListDataObjectModified);
	}
}

void UWidget_ListEntry_Base::OnListDataObjectModified(UListDataObject_Base* ModifiedData,
                                                      EOptionsListDataModifyReason ModifyReason)
{
}

void UWidget_ListEntry_Base::SelectedThisEntryWidget()
{
	CastChecked<UGameUIListView>(GetOwningListView())->SetSelectedItem(GetListItem());
}

FReply UWidget_ListEntry_Base::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	UCommonInputSubsystem* CommonInputSubsystem = GetInputSubsystem();

	if (CommonInputSubsystem && CommonInputSubsystem->GetCurrentInputType() == ECommonInputType::Gamepad)
	{
		if (UWidget* WidgetToFocus = BP_GetWidgetToFocusForGamepad())
		{
			if (TSharedPtr<SWidget> SlateWidgetForFocus = WidgetToFocus->GetCachedWidget())
			{
				return FReply::Handled().SetUserFocus(SlateWidgetForFocus.ToSharedRef());
			}
		}
	}
	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}
