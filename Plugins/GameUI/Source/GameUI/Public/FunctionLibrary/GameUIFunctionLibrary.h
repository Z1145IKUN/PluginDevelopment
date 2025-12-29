// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameUIFunctionLibrary.generated.h"

class UWidget_ActivatableBase;
/**
 * 
 */
UCLASS()
class GAMEUI_API UGameUIFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "GameUI|FunctionLibrary")
	static TSoftClassPtr<UWidget_ActivatableBase> GetSoftWidgetClassByTag(
		UPARAM(meta=(Categories = "GameUI.Widget")) FGameplayTag InWidgetTag);

	UFUNCTION(BlueprintPure, Category = "GameUI|FunctionLibrary")
	static TSoftObjectPtr<UTexture2D> GetSoftImageByTag(
		UPARAM(meta=(Categories = "GameUI.Image")) FGameplayTag InImageTag);

	template <typename EnumType>
	static EnumType StringToEnum(const FString& InString)
	{
		const UEnum* StaticEnumValue = StaticEnum<EnumType>();
		return static_cast<EnumType>(StaticEnumValue->GetValueByNameString(InString));
	}

	template <typename EnumType>
	static FString EnumToString(EnumType InEnumValue)
	{
		const UEnum* StaticEnumValue = StaticEnum<EnumType>();
		return StaticEnumValue->GetNameStringByValue(InEnumValue);
	}
};
