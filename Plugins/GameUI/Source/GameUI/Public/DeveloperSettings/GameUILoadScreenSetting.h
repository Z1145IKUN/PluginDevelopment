// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameUILoadScreenSetting.generated.h"

class UUserWidget;
/**
 * 
 */
UCLASS(Config=Game, DefaultConfig)
class GAMEUI_API UGameUILoadScreenSetting : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	TSubclassOf<UUserWidget> GetLoadScreenWidgetClassChecked() const;

	UPROPERTY(Config, EditAnywhere, Category="Load Screen Settings")
	TSoftClassPtr<UUserWidget> SoftLoadScreenWidgetClass;

	UPROPERTY(Config, EditAnywhere, Category="Load Screen Settings")
	float HoldLoadScreenExtraSeconds = 3.f;

	UPROPERTY(Config, EditAnywhere, Category="Load Screen Settings")
	bool bShouldLoadScreenInEditor = false;
};
