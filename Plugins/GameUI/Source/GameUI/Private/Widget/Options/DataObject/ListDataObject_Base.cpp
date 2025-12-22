// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/DataObject/ListDataObject_Base.h"

TArray<UListDataObject_Base*> UListDataObject_Base::GetAllChildListData() const
{
	return TArray<UListDataObject_Base*>();
}

bool UListDataObject_Base::HasChildListData() const
{
	return false;
}

void UListDataObject_Base::InitDataObject()
{
	OnDataListObjectInitialized();
}

void UListDataObject_Base::OnDataListObjectInitialized()
{
}

void UListDataObject_Base::NotifyListDataModified(UListDataObject_Base* ModifiedListData,
                                                  EOptionsListDataModifyReason ModifyReason)
{
	OnListDataModified.Broadcast(ModifiedListData, ModifyReason);
}
