// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DeveloperSettings.h"
#include "GameUIDeveloperSettings.generated.h"

class UWidget_ActivatableBase;
/**
 * 
 */
UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="GameUI Settings"))
class GAMEUI_API UGameUIDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category="Widget Refence", meta=(ForceInlineRow, Categories ="GameUI.Widget"))
	TMap<FGameplayTag, TSoftClassPtr<UWidget_ActivatableBase>> GameUIWidgetMap;

	UPROPERTY(Config, EditAnywhere, Category="Image Refence", meta=(ForceInlineRow, Categories ="GameUI.Image"))
	TMap<FGameplayTag, TSoftObjectPtr<UTexture2D>> GameUIImageMap;
};
