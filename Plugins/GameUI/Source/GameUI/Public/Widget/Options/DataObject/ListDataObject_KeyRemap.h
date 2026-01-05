// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonInputTypeEnum.h"
#include "ListDataObject_Base.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "ListDataObject_KeyRemap.generated.h"

class UEnhancedPlayerMappableKeyProfile;
class UEnhancedInputUserSettings;
/**
 * 
 */
UCLASS()
class GAMEUI_API UListDataObject_KeyRemap : public UListDataObject_Base
{
	GENERATED_BODY()

public:
	void InitKeyRemapData(
		UEnhancedInputUserSettings* InInputUserSettings,
		UEnhancedPlayerMappableKeyProfile* InKeyRemapProfile,
		ECommonInputType InInputType,
		const FPlayerKeyMapping& InPlayerKeyMapping
	);

private:
	UPROPERTY(Transient)
	TObjectPtr<UEnhancedInputUserSettings> OwningInputUserSettings;

	UPROPERTY(Transient)
	TObjectPtr<UEnhancedPlayerMappableKeyProfile> OwningKeyProfile;

	ECommonInputType DesiredInputType;

	FName OwningMappingName;

	EPlayerMappableKeySlot OwningMappableKeySlot;
};
