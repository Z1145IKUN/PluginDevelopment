// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/GameUIFunctionLibrary.h"
#include "DeveloperSettings/GameUIDeveloperSettings.h"

TSoftClassPtr<UWidget_ActivatableBase> UGameUIFunctionLibrary::GetSoftWidgetClassByTag(FGameplayTag InWidgetTag)
{
	const UGameUIDeveloperSettings* GameUIDeveloperSettings = GetDefault<UGameUIDeveloperSettings>();

	check(GameUIDeveloperSettings->GameUIWidgetMap.Contains(InWidgetTag))

	return GameUIDeveloperSettings->GameUIWidgetMap.FindRef(InWidgetTag);
}

TSoftObjectPtr<UTexture2D> UGameUIFunctionLibrary::GetSoftImageByTag(FGameplayTag InImageTag)
{
	const UGameUIDeveloperSettings* GameUIDeveloperSettings = GetDefault<UGameUIDeveloperSettings>();

	check(GameUIDeveloperSettings->GameUIImageMap.Contains(InImageTag))

	return GameUIDeveloperSettings->GameUIImageMap.FindRef(InImageTag);
}
