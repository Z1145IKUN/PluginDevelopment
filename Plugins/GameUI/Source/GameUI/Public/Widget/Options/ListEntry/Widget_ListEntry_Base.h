// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "GameUITypes/GameUIEnums.h"
#include "Widget_ListEntry_Base.generated.h"

class UCommonTextBlock;
class UListDataObject_Base;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta=(DisableNativeTick))
class GAMEUI_API UWidget_ListEntry_Base : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	//~ Begin IUserObjectListEntry Interface
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	//~ Begin IUserObjectListEntry Interface

	/**
	 * the child class should override it to handle the initialization needed
	 * @param InListDataObject 
	 */
	virtual void OnListDataObjectSet(UListDataObject_Base* InListDataObject);

	/**
	 * the child class should override this function to update UI values after the data object has been modified
	 * the super call is not needed
	 * @param ModifiedData 
	 * @param ModifyReason 
	 */
	virtual void OnListDataObjectModified(UListDataObject_Base* ModifiedData,
	                                      EOptionsListDataModifyReason ModifyReason);

private:
	//***** Bound Widget *****//
	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional, AllowPrivateAccess = "true"))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_SettingDisplayName;
	//***** Bound Widget *****//
};
