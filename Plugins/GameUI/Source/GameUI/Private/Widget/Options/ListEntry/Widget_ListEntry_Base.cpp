// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/ListEntry/Widget_ListEntry_Base.h"
#include "CommonInputSubsystem.h"
#include "CommonTextBlock.h"
#include "Widget/Component/GameUIListView.h"
#include "Widget/Options/DataObject/ListDataObject_Base.h"

void UWidget_ListEntry_Base::NativeOnListEntryWidgetHovered(bool bWasHovered)
{
	BP_OnListEntryWidgetHovered(bWasHovered, GetListItem() ? IsListItemSelected() : false);
}

void UWidget_ListEntry_Base::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	OnListDataObjectSet(CastChecked<UListDataObject_Base>(ListItemObject));
}

void UWidget_ListEntry_Base::NativeOnEntryReleased()
{
	IUserObjectListEntry::NativeOnEntryReleased();

	NativeOnListEntryWidgetHovered(false);
}

void UWidget_ListEntry_Base::OnListDataObjectSet(UListDataObject_Base* InListDataObject)
{
	ListDataObject = InListDataObject;
	if (CommonTextBlock_SettingDisplayName)
	{
		CommonTextBlock_SettingDisplayName->SetText(InListDataObject->GetDataDisplayName());
	}

	if (!InListDataObject->OnListDataModified.IsBoundToObject(this))
	{
		InListDataObject->OnListDataModified.AddUObject(this, &ThisClass::OnListDataObjectModified);
	}

	if (!InListDataObject->OnDependencyDataModified.IsBoundToObject(this))
	{
		InListDataObject->OnDependencyDataModified.AddUObject(this, &ThisClass::OnDependencyDataModified);
	}

	OnToggleEditableState(InListDataObject->IsDataCurrentlyEditable());
}

void UWidget_ListEntry_Base::OnListDataObjectModified(UListDataObject_Base* ModifiedData,
                                                      EOptionsListDataModifyReason ModifyReason)
{
}

void UWidget_ListEntry_Base::OnToggleEditableState(bool bIsEditable)
{
	if (CommonTextBlock_SettingDisplayName)
	{
		CommonTextBlock_SettingDisplayName->SetIsEnabled(bIsEditable);
	}
}

void UWidget_ListEntry_Base::OnDependencyDataModified(UListDataObject_Base* DependencyModifiedData,
                                                      EOptionsListDataModifyReason ModifyReason)
{
	if (ListDataObject)
	{
		OnToggleEditableState(ListDataObject->IsDataCurrentlyEditable());
	}
}

void UWidget_ListEntry_Base::SelectedThisEntryWidget() const
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
