// Fill out your copyright notice in the Description page of Project Settings.


#include "DeveloperSettings/GameUIGameUserSettings.h"

UGameUIGameUserSettings* UGameUIGameUserSettings::Get()
{
	if (GEngine)
	{
		return CastChecked<UGameUIGameUserSettings>(GEngine->GetGameUserSettings());
	}
	return nullptr;
}
