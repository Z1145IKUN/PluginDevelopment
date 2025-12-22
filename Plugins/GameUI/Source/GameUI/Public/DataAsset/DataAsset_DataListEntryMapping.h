// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_DataListEntryMapping.generated.h"

class UListDataObject_Base;
class UWidget_ListEntry_Base;
/**
 * 
 */
UCLASS()
class GAMEUI_API UDataAsset_DataListEntryMapping : public UDataAsset
{
	GENERATED_BODY()

public:
	/**
	 * Obtain the actual class of the data object through GetClass(), and then traverse up the inheritance chain
	 * @param InListData An instance pointer of a list data object
	 * @return 
	 */
	TSubclassOf<UWidget_ListEntry_Base> GetListEntryByListData(UListDataObject_Base* InListData);

private:
	UPROPERTY(EditDefaultsOnly)
	TMap<TSubclassOf<UListDataObject_Base>, TSubclassOf<UWidget_ListEntry_Base>> ListDataListEntryMap;
};
