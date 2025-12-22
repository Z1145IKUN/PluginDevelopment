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

void UListDataObject_String::AdvanceToPreviousOption()
{
	if (AvailableOptionsStringArray.IsEmpty() || AvailableOptionsTextArray.IsEmpty())
	{
		return;
	}
	const int32 CurrentStringValueIndex = AvailableOptionsStringArray.IndexOfByKey(CurrentStringValue);
	const int32 PreviousStringValueIndex = CurrentStringValueIndex - 1;

	if (bool bIsPreviousIndexValid = AvailableOptionsStringArray.IsValidIndex(PreviousStringValueIndex))
	{
		CurrentStringValue = AvailableOptionsStringArray[PreviousStringValueIndex];
	}
	else
	{
		CurrentStringValue = AvailableOptionsStringArray.Last();
	}
	SetDisplayTextFromCurrentStringValue(CurrentStringValue);
	NotifyListDataModified(this);
}

void UListDataObject_String::AdvanceToNextOption()
{
	if (AvailableOptionsStringArray.IsEmpty() || AvailableOptionsTextArray.IsEmpty())
	{
		return;
	}
	const int32 CurrentStringValueIndex = AvailableOptionsStringArray.IndexOfByKey(CurrentStringValue);
	const int32 NextStringValueIndex = CurrentStringValueIndex + 1;

	if (bool bIsNextIndexValid = AvailableOptionsStringArray.IsValidIndex(NextStringValueIndex))
	{
		CurrentStringValue = AvailableOptionsStringArray[NextStringValueIndex];
	}
	else
	{
		CurrentStringValue = AvailableOptionsStringArray[0];
	}
	SetDisplayTextFromCurrentStringValue(CurrentStringValue);
	NotifyListDataModified(this);
}

void UListDataObject_String::OnDataListObjectInitialized()
{
	if (!AvailableOptionsStringArray.IsEmpty())
	{
		CurrentStringValue = AvailableOptionsStringArray[0];
	}

	//TODO: Reade from current string and use it to set the CurrentStringValue

	if (!SetDisplayTextFromCurrentStringValue(CurrentStringValue))
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
