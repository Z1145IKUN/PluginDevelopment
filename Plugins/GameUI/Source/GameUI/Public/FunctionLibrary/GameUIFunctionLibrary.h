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
};
