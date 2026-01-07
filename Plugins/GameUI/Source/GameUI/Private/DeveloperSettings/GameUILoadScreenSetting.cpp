// Fill out your copyright notice in the Description page of Project Settings.


#include "DeveloperSettings/GameUILoadScreenSetting.h"
#include "Blueprint/UserWidget.h"

TSubclassOf<UUserWidget> UGameUILoadScreenSetting::GetLoadScreenWidgetClassChecked() const
{
	check(!SoftLoadScreenWidgetClass.IsNull())

	TSubclassOf<UUserWidget> LoadedLoadingScreenWidget = SoftLoadScreenWidgetClass.LoadSynchronous();

	return LoadedLoadingScreenWidget;
}
