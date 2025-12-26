// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/ListEntry/Widget_ListEntry_Scalar.h"

#include "AnalogSlider.h"
#include "Widget/Options/DataObject/ListDataObject_Scalar.h"

void UWidget_ListEntry_Scalar::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	AnalogSlider_SettingSlider->OnValueChanged.AddUniqueDynamic(this, &ThisClass::OnSliderValueChanged);
}

void UWidget_ListEntry_Scalar::OnListDataObjectSet(UListDataObject_Base* InListDataObject)
{
	Super::OnListDataObjectSet(InListDataObject);

	ScalarDataObject = CastChecked<UListDataObject_Scalar>(InListDataObject);

	CommonNumericTextBlock_SettingValue->SetNumericType(ScalarDataObject->GetDisplayNumericType());
	CommonNumericTextBlock_SettingValue->FormattingSpecification = ScalarDataObject->GetNumberFormattingOptions();
	CommonNumericTextBlock_SettingValue->SetCurrentValue(ScalarDataObject->GetCurrentValue());

	AnalogSlider_SettingSlider->SetMinValue(ScalarDataObject->GetDisplayValueRange().GetLowerBoundValue());
	AnalogSlider_SettingSlider->SetMaxValue(ScalarDataObject->GetDisplayValueRange().GetUpperBoundValue());
	AnalogSlider_SettingSlider->SetStepSize(ScalarDataObject->GetSliderStepSize());
	AnalogSlider_SettingSlider->SetValue(ScalarDataObject->GetCurrentValue());
}

void UWidget_ListEntry_Scalar::OnListDataObjectModified(UListDataObject_Base* ModifiedData,
                                                        EOptionsListDataModifyReason ModifyReason)
{
	if (ScalarDataObject)
	{
		CommonNumericTextBlock_SettingValue->SetCurrentValue(ScalarDataObject->GetCurrentValue());
		AnalogSlider_SettingSlider->SetValue(ScalarDataObject->GetCurrentValue());
	}
}

void UWidget_ListEntry_Scalar::OnSliderValueChanged(float InNewValue)
{
	if (ScalarDataObject)
	{
		ScalarDataObject->SetCurrentValueFromSlider(InNewValue);
	}
}
