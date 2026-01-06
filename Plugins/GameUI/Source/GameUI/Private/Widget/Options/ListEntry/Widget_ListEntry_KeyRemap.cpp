// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/ListEntry/Widget_ListEntry_KeyRemap.h"

#include "Widget/Component/GameUIButtonBase.h"
#include "Widget/Options/DataObject/ListDataObject_KeyRemap.h"

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
