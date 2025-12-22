// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ListDataObject_Value.h"
#include "ListDataObject_String.generated.h"

/**
 * 
 */
UCLASS()
class GAMEUI_API UListDataObject_String : public UListDataObject_Value
{
	GENERATED_BODY()

public:
	void AddDynamicOptions(const FString& InStringValue, const FText& InDisplayText);

	const TArray<FText>& GetAvailableOptionsTextArray() const;

protected:
	//~ Begin UListDataObject_Base interface
	virtual void OnDataListObjectInitialized() override;
	//~ End UListDataObject_Base interface

	bool SetDisplayTextFromCurrentStringValue(const FString& InCurrentStringValue);

	FString CurrentStringValue;
	FText CurrentDisplayText;
	TArray<FString> AvailableOptionsStringArray;
	TArray<FText> AvailableOptionsTextArray;
};
