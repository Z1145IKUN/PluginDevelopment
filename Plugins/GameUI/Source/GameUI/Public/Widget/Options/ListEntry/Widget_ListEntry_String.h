// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Options/ListEntry/Widget_ListEntry_Base.h"
#include "Widget_ListEntry_String.generated.h"

class UGameUIButtonBase;
class UGameUIRotator;
class UListDataObject_String;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta=(DisableNativeTick))
class GAMEUI_API UWidget_ListEntry_String : public UWidget_ListEntry_Base
{
	GENERATED_BODY()

protected:
	//~ Begin UWidget_ListEntry_Base interface
	virtual void OnListDataObjectSet(UListDataObject_Base* InListDataObject) override;
	//~ Begin UWidget_ListEntry_Base interface

private:
	//***** Bound Widget *****//
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UGameUIButtonBase> CommonButton_Previous;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UGameUIRotator> CommonRotator_Options;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UGameUIButtonBase> CommonButton_Next;
	//***** Bound Widget *****//

	UPROPERTY(Transient)
	TObjectPtr<UListDataObject_String> StringListDataObject;
};
