// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameUITypes/GameUIEnums.h"
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

	LIST_DATA_ACCESSOR(FName, DataID)
	LIST_DATA_ACCESSOR(FText, DataDisplayName)
	LIST_DATA_ACCESSOR(FText, DescriptionRichText)
	LIST_DATA_ACCESSOR(FText, DisableRichText)
	LIST_DATA_ACCESSOR(TSoftObjectPtr<UTexture2D>, SoftDescriptionImage)
	LIST_DATA_ACCESSOR(UListDataObject_Base*, ParentData)

	/**
	 * the parent is empty ,the child class should override it ,
	 * the function should return all the child data that tab has
	 * @return 
	 */
	virtual TArray<UListDataObject_Base*> GetAllChildListData() const;

	/**
	 * the parent is empty ,the child class should override it ,
	 * @return 
	 */
	virtual bool HasChildListData() const;

	void InitDataObject();

	void SetShouldApplySettingsImmediately(bool InShouldApplySettingsImmediately);

protected:
	/**
	 * is empty in the base class
	 * child class should override it to initialize itself
	 */
	virtual void OnDataListObjectInitialized();

	virtual void NotifyListDataModified(
		UListDataObject_Base* ModifiedListData,
		EOptionsListDataModifyReason ModifyReason = EOptionsListDataModifyReason::DirectlyModify);

private:
	FName DataID;
	FText DataDisplayName;
	FText DescriptionRichText;
	FText DisableRichText;
	TSoftObjectPtr<UTexture2D> SoftDescriptionImage;

	UPROPERTY(Transient)
	TObjectPtr<UListDataObject_Base> ParentData;

	bool bShouldApplyChangesImmediately = false;
};
