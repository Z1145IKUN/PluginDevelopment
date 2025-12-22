// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/DataObject/ListDataObject_String.h"

void UListDataObject_String::AddDynamicOptions(const FString& InStringValue, const FText& InDisplayText)
{
	AvailableOptionsStringArray.Add(InStringValue);
	AvailableOptionsTextArray.Add(InDisplayText);
}

const TArray<FText>& UListDataObject_String::GetAvailableOptionsTextArray() const
{
	return AvailableOptionsTextArray;
}

const FText& UListDataObject_String::GetCurrentDisplayText() const
{
	return CurrentDisplayText;
}

void UListDataObject_String::OnDataListObjectInitialized()
{
	if (!AvailableOptionsStringArray.IsEmpty())
	{
		CurrentStringValue = AvailableOptionsStringArray[0];
	}

	//TODO: Reade from current string and use it to set the CurrentStringValue

	if (SetDisplayTextFromCurrentStringValue(CurrentStringValue))
	{
		CurrentDisplayText = FText::FromString(TEXT("Invalid Option"));
	}
}

bool UListDataObject_String::SetDisplayTextFromCurrentStringValue(const FString& InCurrentStringValue)
{
	const int32 CurrentStringValueIndex = AvailableOptionsStringArray.IndexOfByKey(InCurrentStringValue);

	if (AvailableOptionsTextArray.IsValidIndex(CurrentStringValueIndex))
	{
		CurrentDisplayText = AvailableOptionsTextArray[CurrentStringValueIndex];
		return true;
	}

	return false;
}
