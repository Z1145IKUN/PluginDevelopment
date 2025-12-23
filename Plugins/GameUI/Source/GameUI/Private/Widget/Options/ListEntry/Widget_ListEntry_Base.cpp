// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/ListEntry/Widget_ListEntry_Base.h"

#include "CommonTextBlock.h"
#include "Widget/Options/DataObject/ListDataObject_Base.h"

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
