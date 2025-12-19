// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/DataObject/ListDataObject_Collection.h"

TArray<UListDataObject_Base*> UListDataObject_Collection::GetAllChildListData() const
{
	return ChildListDataArray;
}

bool UListDataObject_Collection::HasChildListData() const
{
	return !ChildListDataArray.IsEmpty();
}

void UListDataObject_Collection::AddChildListData(UListDataObject_Base* InChildListData)
{
	//notify the child list data ti init itself
	InChildListData->InitDataObject();

	//Set child list data parent to this
	InChildListData->SetParentData(this);

	ChildListDataArray.Add(InChildListData);
}
