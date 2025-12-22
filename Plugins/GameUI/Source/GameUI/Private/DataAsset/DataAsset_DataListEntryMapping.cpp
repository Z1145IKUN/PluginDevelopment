// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/DataAsset_DataListEntryMapping.h"

#include "Widget/Options/DataObject/ListDataObject_Base.h"

TSubclassOf<UWidget_ListEntry_Base> UDataAsset_DataListEntryMapping::GetListEntryByListData(
	UListDataObject_Base* InListData)
{
	check(InListData);

	for (UClass* ListDataClass = InListData->GetClass(); ListDataClass; ListDataClass = ListDataClass->GetSuperClass())
	{
		if (TSubclassOf<UListDataObject_Base> ConvertedListData = TSubclassOf<UListDataObject_Base>(ListDataClass))
		{
			if (ListDataListEntryMap.Contains(ConvertedListData))
			{
				return ListDataListEntryMap.FindRef(ConvertedListData);
			}
		}
	}

	return TSubclassOf<UWidget_ListEntry_Base>();
}
