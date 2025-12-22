// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/ListEntry/Widget_ListEntry_String.h"

#include "Widget/Component/GameUIRotator.h"
#include "Widget/Options/DataObject/ListDataObject_String.h"

void UWidget_ListEntry_String::OnListDataObjectSet(UListDataObject_Base* InListDataObject)
{
	Super::OnListDataObjectSet(InListDataObject);

	StringListDataObject = CastChecked<UListDataObject_String>(InListDataObject);

	CommonRotator_Options->PopulateTextLabels(StringListDataObject->GetAvailableOptionsTextArray());
	CommonRotator_Options->SetSelectedOptionByText(StringListDataObject->GetCurrentDisplayText());
}
