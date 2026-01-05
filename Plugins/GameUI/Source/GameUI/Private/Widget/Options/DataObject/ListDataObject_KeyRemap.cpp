// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/DataObject/ListDataObject_KeyRemap.h"

void UListDataObject_KeyRemap::InitKeyRemapData(
	UEnhancedInputUserSettings* InInputUserSettings,
	UEnhancedPlayerMappableKeyProfile* InKeyRemapProfile,
	ECommonInputType InInputType,
	const FPlayerKeyMapping& InPlayerKeyMapping)
{
	OwningInputUserSettings = InInputUserSettings;
	OwningKeyProfile = InKeyRemapProfile;
	DesiredInputType = InInputType;
	OwningMappingName = InPlayerKeyMapping.GetMappingName();
	OwningMappableKeySlot = InPlayerKeyMapping.GetSlot();
}
