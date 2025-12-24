// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameUITypes/GameUIEnums.h"
#include "Widget/Widget_ActivatableBase.h"
#include "Widget_OptionScreen.generated.h"

class UOptionDataRegistry;
class UWidget_TabListWidgetBase;
class UGameUIListView;
class UWidget_OptionDetailsView;
class UListDataObject_Base;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta=(DisableNativeTick))
class GAMEUI_API UWidget_OptionScreen : public UWidget_ActivatableBase
{
	GENERATED_BODY()

protected:
	// ~Begin UUserWidget interface
	virtual void NativeOnInitialized() override;
	// ~End UUserWidget interface

	//~ Begin UCommonActivatableWidget interface
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	//~ End UCommonActivatableWidget Interface

private:
	void OnResetActionTriggered();
	void OnBackActionTriggered();

	void OnListViewItemHoveredChanged(UObject* InHoveredItem, bool bWasHovered);
	void OnListViewItemSelectedChanged(UObject* InSelectedItem);

	UFUNCTION()
	void OnOptionsTabSelected(FName TabID);

	UOptionDataRegistry* GetOrCreateOptionDataRegistry();

	//***** Bound Widget *****//
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UWidget_TabListWidgetBase> TabListWidget_OptionsTab;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UGameUIListView> ListView_OptionsList;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UWidget_OptionDetailsView> DetailsView_ListEntry;
	//***** Bound Widget *****//


	// reset action data table handle
	UPROPERTY(EditDefaultsOnly,
		Category = "GameUI|OptionScreen",
		meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;

	//Reset binding action handle
	FUIActionBindingHandle ResetAction_Handle;

	//Handle the creation operation of data in the option Screen. Direct access to this variable is forbidden.
	UPROPERTY(Transient)
	TObjectPtr<UOptionDataRegistry> OwningOptionDataRegistry;

	UPROPERTY(Transient)
	TArray<UListDataObject_Base*> ResettableListDataArray;

	//It is called every time when List data modified
	void OnListViewListDataModified(UListDataObject_Base* ModifiedData, EOptionsListDataModifyReason ModifiedReason);
};
