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

ECommonInputType UListDataObject_KeyRemap::GetDesiredInputType() const
{
	return DesiredInputType;
}

void UListDataObject_KeyRemap::BindNewInputKey(const FKey& InNewKey)
{
	check(OwningInputUserSettings);

	FMapPlayerKeyArgs KeyArgs;
	KeyArgs.MappingName = OwningMappingName;
	KeyArgs.Slot = OwningMappableKeySlot;
	KeyArgs.NewKey = InNewKey;

	FGameplayTagContainer Container;

	OwningInputUserSettings->MapPlayerKey(KeyArgs, Container);
	OwningInputUserSettings->SaveSettings();

	NotifyListDataModified(this);
}

bool UListDataObject_KeyRemap::HasDefaultValue() const
{
	return GetOwningKeyMapping()->GetDefaultKey().IsValid();
}

bool UListDataObject_KeyRemap::CanResetBackToDefaultValue() const
{
	return HasDefaultValue() && GetOwningKeyMapping()->IsCustomized();
}

bool UListDataObject_KeyRemap::TryResetBackToDefaultValue()
{
	if (CanResetBackToDefaultValue())
	{
		check(OwningInputUserSettings);

		GetOwningKeyMapping()->ResetToDefault();
		OwningInputUserSettings->SaveSettings();

		NotifyListDataModified(this, EOptionsListDataModifyReason::ResetToDefault);
		return true;
	}
	return false;
}

FPlayerKeyMapping* UListDataObject_KeyRemap::GetOwningKeyMapping() const
{
	check(OwningKeyProfile);
	FMapPlayerKeyArgs KeyArgs;
	KeyArgs.MappingName = OwningMappingName;
	KeyArgs.Slot = OwningMappableKeySlot;

	return OwningKeyProfile->FindKeyMapping(KeyArgs);
}
