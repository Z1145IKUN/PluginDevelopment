// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Options/DataObject/ListDataObject_String.h"
#include "ListDataObject_StringResolution.generated.h"

/**
 * 
 */
UCLASS()
class GAMEUI_API UListDataObject_StringResolution : public UListDataObject_String
{
	GENERATED_BODY()

public:
	void InitResolutionValues();

	FString GetMaxAllowResolution();

protected:
	//~ Begin UListDataObject_Base interface
	virtual void OnDataListObjectInitialized() override;
	//~ End UListDataObject_Base interface

private:
	FString ResolutionValueToString(const FIntPoint& InResolutionValue) const;
	FText ResolutionValueToText(const FIntPoint& InResolutionValue) const;

	FString MaxAllowResolution;
};
