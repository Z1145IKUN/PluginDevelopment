// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/DataObject/ListDataObject_KeyRemap.h"

#include "CommonInputBaseTypes.h"
#include "CommonInputSubsystem.h"

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

FSlateBrush UListDataObject_KeyRemap::GetIconFromCurrentKey() const
{
	check(OwningInputUserSettings);

	FSlateBrush FoundBrush;
	UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(OwningInputUserSettings->GetLocalPlayer());
	check(CommonInputSubsystem);

	const bool bHasFoundBrush = UCommonInputPlatformSettings::Get()->TryGetInputBrush(
		FoundBrush,
		GetOwningKeyMapping()->GetCurrentKey(),
		DesiredInputType,
		CommonInputSubsystem->GetCurrentGamepadName()
	);

	return FoundBrush;
}

FPlayerKeyMapping* UListDataObject_KeyRemap::GetOwningKeyMapping() const
{
	check(OwningKeyProfile);
	FMapPlayerKeyArgs KeyArgs;
	KeyArgs.MappingName = OwningMappingName;
	KeyArgs.Slot = OwningMappableKeySlot;

	return OwningKeyProfile->FindKeyMapping(KeyArgs);
}
