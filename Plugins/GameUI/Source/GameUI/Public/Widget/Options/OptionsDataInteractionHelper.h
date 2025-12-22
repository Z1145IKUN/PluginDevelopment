// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyPathHelpers.h"

class UGameUIGameUserSettings;
/**
 * 
 */
class GAMEUI_API FOptionsDataInteractionHelper
{
public:
	FOptionsDataInteractionHelper(const FString& InGetterOrSetterFuncPath);

	FString GetValueAsString();
	void SetValueFromString(const FString& InStringValue);

private:
	FCachedPropertyPath CachedDynamicFunctionPath;
	TWeakObjectPtr<UGameUIGameUserSettings> CachedWeakGameUserSettings;
};
