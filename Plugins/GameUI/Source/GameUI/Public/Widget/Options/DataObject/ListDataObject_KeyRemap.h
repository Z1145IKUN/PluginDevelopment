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

	FSlateBrush GetIconFromCurrentKey() const;

	ECommonInputType GetDesiredInputType() const;

	void BindNewInputKey(const FKey& InNewKey);

	// ~ Begin UListDataObject_Base interface
	virtual bool HasDefaultValue() const override;
	virtual bool CanResetBackToDefaultValue() const override;
	virtual bool TryResetBackToDefaultValue() override;
	// ~ End UListDataObject_Base interface

private:
	FPlayerKeyMapping* GetOwningKeyMapping() const;

	UPROPERTY(Transient)
	TObjectPtr<UEnhancedInputUserSettings> OwningInputUserSettings;

	UPROPERTY(Transient)
	TObjectPtr<UEnhancedPlayerMappableKeyProfile> OwningKeyProfile;

	ECommonInputType DesiredInputType;

	FName OwningMappingName;

	EPlayerMappableKeySlot OwningMappableKeySlot;
};
