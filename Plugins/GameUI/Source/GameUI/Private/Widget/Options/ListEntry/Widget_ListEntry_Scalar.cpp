// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/ListEntry/Widget_ListEntry_Scalar.h"

void UWidget_ListEntry_Scalar::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UWidget_ListEntry_Scalar::OnListDataObjectSet(UListDataObject_Base* InListDataObject)
{
	Super::OnListDataObjectSet(InListDataObject);
}

void UWidget_ListEntry_Scalar::OnListDataObjectModified(UListDataObject_Base* ModifiedData,
                                                        EOptionsListDataModifyReason ModifyReason)
{
}
