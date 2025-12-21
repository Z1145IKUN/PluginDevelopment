// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/ListEntry/Widget_ListEntry_Base.h"

void UWidget_ListEntry_Base::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
}
