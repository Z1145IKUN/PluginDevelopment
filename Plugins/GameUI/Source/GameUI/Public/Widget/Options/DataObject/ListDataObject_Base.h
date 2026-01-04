// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameUITypes/GameUIEnums.h"
#include "GameUITypes/GameUIStructs.h"
#include "ListDataObject_Base.generated.h"

#define LIST_DATA_ACCESSOR(DataType,PropertyName) \
	FORCEINLINE DataType Get##PropertyName() const { return PropertyName; } \
	void Set##PropertyName(DataType In##PropertyName) { PropertyName = In##PropertyName; }
/**
 * 
 */
UCLASS()
class GAMEUI_API UListDataObject_Base : public UObject
{
	GENERATED_BODY()

public:
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnListDataModifiedDelegate,
	                                     UListDataObject_Base*,
	                                     EOptionsListDataModifyReason)

	FOnListDataModifiedDelegate OnListDataModified;
	FOnListDataModifiedDelegate OnDependencyDataModified;

	LIST_DATA_ACCESSOR(FName, DataID)
	LIST_DATA_ACCESSOR(FText, DataDisplayName)
	LIST_DATA_ACCESSOR(FText, DescriptionRichText)
	LIST_DATA_ACCESSOR(FText, DisableRichText)
	LIST_DATA_ACCESSOR(TSoftObjectPtr<UTexture2D>, SoftDescriptionImage)
	LIST_DATA_ACCESSOR(UListDataObject_Base*, ParentData)

	/**
	 * the parent is empty ,the child class ListDataObject_Collection should override it ,
	 * the function should return all the child data that tab has
	 */
	virtual TArray<UListDataObject_Base*> GetAllChildListData() const;

	/**
	 * the parent is empty ,the child class should override it , 
	 */
	virtual bool HasChildListData() const;

	void InitDataObject();

	void SetShouldApplySettingsImmediately(bool InShouldApplySettingsImmediately);

	/**
	 * the child class should override them to provide implementations for reset data
	 */
	virtual bool HasDefaultValue() const;
	virtual bool CanResetBackToDefaultValue() const;
	virtual bool TryResetBackToDefaultValue();

	//Get call by from OptionsDataRegistry for adding in edit condition for the constructed list data object
	void AddEditCondition(const FOptionsDataEditConditionDescriptor& InEditCondition);

	bool IsDataCurrentlyEditable();

	//Get call by from OptionsDataRegistry to add in dependency data 
	void AddEditDependencyData(UListDataObject_Base* InDependencyData);

protected:
	/**
	 * is empty in the base class
	 * child class should override it to initialize itself
	 * It will be called only when it is added to parent data.
	 */
	virtual void OnDataListObjectInitialized();

	virtual void NotifyListDataModified(
		UListDataObject_Base* ModifiedListData,
		EOptionsListDataModifyReason ModifyReason = EOptionsListDataModifyReason::DirectlyModify);


	/**
	 * the child class should override this to allow the value to be set the force string value;
	 */
	virtual bool CanSetToForceStringValue(const FString& InForceStringValue) const;

	/**
	 * the child class should override this to specify how to set the current value to the force value
	 * the super call is not needed
	 */
	virtual void OnSetToForceStringValue(const FString& InForceStringValue);

	/**
	 * this function will be called when the value of the dependency data has changed
	 * the child class can override this function to handle the custom logic needed,
	 * super call is expected
	 */
	virtual void OnEditDependencyDataModified(
		UListDataObject_Base* ModifiedDependencyData,
		EOptionsListDataModifyReason ModifyReason);

private:
	FName DataID;
	FText DataDisplayName;
	FText DescriptionRichText;
	FText DisableRichText;
	TSoftObjectPtr<UTexture2D> SoftDescriptionImage;

	UPROPERTY(Transient)
	TObjectPtr<UListDataObject_Base> ParentData;

	bool bShouldApplyChangesImmediately = false;

	UPROPERTY(Transient)
	TArray<FOptionsDataEditConditionDescriptor> EditConditionDescriptorArray;
};
