// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/GameUIFunctionLibrary.h"
#include "DeveloperSettings/GameUIDeveloperSettings.h"

TSoftClassPtr<UWidget_ActivatableBase> UGameUIFunctionLibrary::GetSoftWidgetClassByTag(FGameplayTag InWidgetTag)
{
	const UGameUIDeveloperSettings* FrontEndDeveloperSettings = GetDefault<UGameUIDeveloperSettings>();

	check(FrontEndDeveloperSettings->GameUIWidgetMap.Contains(InWidgetTag))

	return FrontEndDeveloperSettings->GameUIWidgetMap.FindRef(InWidgetTag);
}
