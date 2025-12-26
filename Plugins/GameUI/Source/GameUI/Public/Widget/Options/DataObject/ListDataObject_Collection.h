// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ListDataObject_Base.h"
#include "ListDataObject_Collection.generated.h"

/**
 * 
 */
UCLASS()
class GAMEUI_API UListDataObject_Collection : public UListDataObject_Base
{
	GENERATED_BODY()
	
public:
	//~ Begin UListDataObject_Base interface
	virtual TArray<UListDataObject_Base*> GetAllChildListData() const override;
	virtual bool HasChildListData() const override;
	//~ End UListDataObject_Base interface
	
	void AddChildListData(UListDataObject_Base* InChildListData);
	
private:
	UPROPERTY(Transient)
	TArray<UListDataObject_Base*> ChildListDataArray;
};
