// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/DataObject/ListDataObject_Scalar.h"

#include "Widget/Options/OptionsDataInteractionHelper.h"

FCommonNumberFormattingOptions UListDataObject_Scalar::NoDecimal()
{
	FCommonNumberFormattingOptions Options;
	Options.MaximumFractionalDigits = 0;
	return Options;
}

FCommonNumberFormattingOptions UListDataObject_Scalar::WithDecimal(int32 NumFracDigit)
{
	FCommonNumberFormattingOptions Options;
	Options.MaximumFractionalDigits = NumFracDigit;
	return Options;
}

float UListDataObject_Scalar::GetCurrentValue()
{
	if (DataDynamicGetter)
	{
		return FMath::GetMappedRangeValueClamped(
			OutputValueRange,
			DisplayValueRange,
			StringToFloat(DataDynamicGetter->GetValueAsString())
		);
	}
	return 0.f;
}

void UListDataObject_Scalar::SetCurrentValueFromSlider(const float InNewValue)
{
	if (DataDynamicSetter)
	{
		const float OutFloatValue = FMath::GetMappedRangeValueClamped(
			DisplayValueRange,
			OutputValueRange,
			InNewValue);

		DataDynamicSetter->SetValueFromString(LexToString(OutFloatValue));

		NotifyListDataModified(this);
	}
}

bool UListDataObject_Scalar::CanResetBackToDefaultValue() const
{
	if (HasDefaultValue() && DataDynamicGetter)
	{
		const float DefaultValue = StringToFloat(GetDefaultValueAsString());
		const float CurrentValue = StringToFloat(DataDynamicGetter->GetValueAsString());

		return !FMath::IsNearlyEqual(DefaultValue, CurrentValue, 0.01f);
	}
	return false;
}

bool UListDataObject_Scalar::TryResetBackToDefaultValue()
{
	if (DataDynamicSetter && CanResetBackToDefaultValue())
	{
		DataDynamicSetter->SetValueFromString(GetDefaultValueAsString());

		NotifyListDataModified(this, EOptionsListDataModifyReason::ResetToDefault);
		return true;
	}
	return false;
}

float UListDataObject_Scalar::StringToFloat(const FString& InString) const
{
	float OutConvertedValue = 0.f;
	LexFromString(OutConvertedValue, *InString);
	return OutConvertedValue;
}
