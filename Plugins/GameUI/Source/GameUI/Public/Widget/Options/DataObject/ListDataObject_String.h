// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ListDataObject_Value.h"
#include "FunctionLibrary/GameUIFunctionLibrary.h"
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
	const FText& GetCurrentDisplayText() const;

	void AdvanceToPreviousOption();
	void AdvanceToNextOption();

	void OnRotatorInitiatedValueChanged(const FText& InNewSelectedText);

protected:
	//~ Begin UListDataObject_Base interface
	virtual void OnDataListObjectInitialized() override;
	virtual bool CanResetBackToDefaultValue() const override;
	virtual bool TryResetBackToDefaultValue() override;
	virtual bool CanSetToForceStringValue(const FString& InForceStringValue) const override;
	virtual void OnSetToForceStringValue(const FString& InForceStringValue) override;
	//~ End UListDataObject_Base interface

	bool SetDisplayTextFromCurrentStringValue(const FString& InCurrentStringValue);

	FString CurrentStringValue;
	FText CurrentDisplayText;
	TArray<FString> AvailableOptionsStringArray;
	TArray<FText> AvailableOptionsTextArray;
};


UCLASS()
class GAMEUI_API UListDataObject_StringBool : public UListDataObject_String
{
	GENERATED_BODY()

public:
	void OverrideTrueDisplayText(const FText& InTrueText);
	void OverrideFalseDisplayText(const FText& InFalseText);

	void SetTrueAsDefaultString();
	void SetFalseAsDefaultString();

protected:
	//~ Begin UListDataObject_Base interface
	virtual void OnDataListObjectInitialized() override;
	//~ End UListDataObject_Base interface

private:
	void TryInitBoolValues();

	const FString TrueString = TEXT("true");
	const FString FalseString = TEXT("false");
};

UCLASS()
class GAMEUI_API UListDataObject_StringEnum : public UListDataObject_String
{
	GENERATED_BODY()

public:
	template <typename EnumType>
	void AddEnumOption(EnumType InEnumOption, const FText& InDisplayText)
	{
		const FString ConvertedEnumString = UGameUIFunctionLibrary::EnumToString(InEnumOption);
		AddDynamicOptions(ConvertedEnumString, InDisplayText);
	}

	template <typename EnumType>
	EnumType GetCurrentValueAsEnum() const
	{
		return UGameUIFunctionLibrary::StringToEnum<EnumType>(CurrentStringValue);
	}

	template <typename EnumType>
	void SetDefaultValueFromEnumOption(EnumType InEnumOption)
	{
		const FString ConvertedEnumString = UGameUIFunctionLibrary::EnumToString(InEnumOption);

		SetDefaultValueFromString(ConvertedEnumString);
	}
};
