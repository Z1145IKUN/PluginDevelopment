// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/DataObject/ListDataObject_Base.h"

TArray<UListDataObject_Base*> UListDataObject_Base::GetAllChildListData() const
{
	return  TArray<UListDataObject_Base*>();
}

bool UListDataObject_Base::HasChildListData() const
{
	return false;
}
