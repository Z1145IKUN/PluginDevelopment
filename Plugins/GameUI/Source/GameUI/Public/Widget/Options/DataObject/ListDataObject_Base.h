// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
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
	LIST_DATA_ACCESSOR(FName,DataID)
	LIST_DATA_ACCESSOR(FText,DataDisplayName)
	LIST_DATA_ACCESSOR(FText,DescriptionRichText)
	LIST_DATA_ACCESSOR(FText,DisableRichText)
	LIST_DATA_ACCESSOR(TSoftObjectPtr<UTexture2D>,SoftDescriptionImage)
	LIST_DATA_ACCESSOR(UListDataObject_Base*,ParentData)

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

private:
	FName DataID;
	FText DataDisplayName;
	FText DescriptionRichText;
	FText DisableRichText;
	TSoftObjectPtr<UTexture2D> SoftDescriptionImage;
	
	UPROPERTY(Transient)
	TObjectPtr<UListDataObject_Base> ParentData;
};
