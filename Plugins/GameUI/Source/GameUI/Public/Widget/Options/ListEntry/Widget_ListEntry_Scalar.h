// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget_ListEntry_Base.h"
#include "Widget_ListEntry_Scalar.generated.h"


class UCommonNumericTextBlock;
class UAnalogSlider;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta=(DisableNativeTick))
class GAMEUI_API UWidget_ListEntry_Scalar : public UWidget_ListEntry_Base
{
	GENERATED_BODY()

protected:
	//~ Begin UUserWidget interface
	virtual void NativeOnInitialized() override;
	//~ End UUserWidget interface

	//~ Begin UWidget_ListEntry_Base interface
	virtual void OnListDataObjectSet(UListDataObject_Base* InListDataObject) override;
	virtual void OnListDataObjectModified(UListDataObject_Base* ModifiedData,
	                                      EOptionsListDataModifyReason ModifyReason) override;
	//~ Begin UWidget_ListEntry_Base interface

private:
	//***** Bound Widget *****//
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	TObjectPtr<UCommonNumericTextBlock> CommonNumericTextBlock_SettingValue;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	TObjectPtr<UAnalogSlider> AnalogSlider_SettingSlider;
	//***** Bound Widget *****//
};
