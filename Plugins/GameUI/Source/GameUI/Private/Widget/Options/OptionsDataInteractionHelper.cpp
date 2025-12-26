// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/OptionsDataInteractionHelper.h"

#include "DeveloperSettings/GameUIGameUserSettings.h"

FOptionsDataInteractionHelper::FOptionsDataInteractionHelper(const FString& InGetterOrSetterFuncPath)
{
	CachedDynamicFunctionPath = InGetterOrSetterFuncPath;
	CachedWeakGameUserSettings = UGameUIGameUserSettings::Get();
}

FString FOptionsDataInteractionHelper::GetValueAsString()
{
	FString OutStringValue;
	PropertyPathHelpers::GetPropertyValueAsString(
		CachedWeakGameUserSettings.Get(),
		CachedDynamicFunctionPath,
		OutStringValue
	);

	return OutStringValue;
}

void FOptionsDataInteractionHelper::SetValueFromString(const FString& InStringValue)
{
	PropertyPathHelpers::SetPropertyValueFromString(
		CachedWeakGameUserSettings.Get(),
		CachedDynamicFunctionPath,
		InStringValue
	);
}
