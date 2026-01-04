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

public:
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="On List Entry Widget Hovered"))
	void BP_OnListEntryWidgetHovered(bool bWasHovered, bool bIsEntryWidgetStillSelected);

	void NativeOnListEntryWidgetHovered(bool bWasHovered);

protected:
	//~ Begin IUserObjectListEntry Interface
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	/**
	 * When this entry is retrieved by the list system,
	 * necessary cleaning and status reset operations should be carried out 
	 * to ensure that the entry does not display an incorrect status 
	 * when it is reused next time.
	 */
	virtual void NativeOnEntryReleased() override;
	//~ Begin IUserObjectListEntry Interface

	/**
	 * the child class should override it to handle the initialization needed
	 */
	virtual void OnListDataObjectSet(UListDataObject_Base* InListDataObject);

	/**
	 * the child class should override this function to update UI values after the data object has been modified
	 * the super call is not needed
	 */
	virtual void OnListDataObjectModified(UListDataObject_Base* ModifiedData,
	                                      EOptionsListDataModifyReason ModifyReason);

	//the child class should override this to change editable state of the widget it owns
	virtual void OnToggleEditableState(bool bIsEditable);

	//the child class should override this to
	virtual void OnDependencyDataModified(UListDataObject_Base* DependencyModifiedData,
	                                      EOptionsListDataModifyReason ModifyReason);

	void SelectedThisEntryWidget() const;

	//~ Begin UUserWidget Interface
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	//~ Begin UUserWidget Interface

	UFUNCTION(BlueprintImplementableEvent, meta=( DisplayName="Get Widget To Focus For Gamepad" ))
	UWidget* BP_GetWidgetToFocusForGamepad() const;

private:
	//***** Bound Widget *****//
	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional, AllowPrivateAccess = "true"))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_SettingDisplayName;
	//***** Bound Widget *****//

	UPROPERTY(Transient)
	TObjectPtr<UListDataObject_Base> ListDataObject;
};
