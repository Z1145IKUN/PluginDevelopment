// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget_ListEntry_Base.h"
#include "Widget_ListEntry_KeyRemap.generated.h"

class UGameUIButtonBase;
class UListDataObject_KeyRemap;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta=(DisableNativeTick))
class GAMEUI_API UWidget_ListEntry_KeyRemap : public UWidget_ListEntry_Base
{
	GENERATED_BODY()

protected:
	//~ Begin UWidget_ListEntry_Base interface
	virtual void OnListDataObjectSet(UListDataObject_Base* InListDataObject) override;
	virtual void OnListDataObjectModified(UListDataObject_Base* ModifiedData,
	                                      EOptionsListDataModifyReason ModifyReason) override;
	//~ End UWidget_ListEntry_Base interface

private:
	//***** Bound Widget *****//
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UGameUIButtonBase> CommonButton_RemapKey;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UGameUIButtonBase> CommonButton_ResetKeyBinding;
	//***** Bound Widget *****//

	UPROPERTY(Transient)
	TObjectPtr<UListDataObject_KeyRemap> KeyRemapListDataObject;
};
