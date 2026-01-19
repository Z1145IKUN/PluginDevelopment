// Fill out your copyright notice in the Description page of Project Settings.


#include "DeveloperSettings/GameUIGameUserSettings.h"

#include "FunctionLibrary/GameUIFunctionLibrary.h"

UGameUIGameUserSettings::UGameUIGameUserSettings()
{
	OverallVolume = 1.f;
	MusicVolume = 1.f;
	SoundFXVolume = 1.f;
	AllowBackgroundAudio = true;
	UseHDRAudio = true;
}

UGameUIGameUserSettings* UGameUIGameUserSettings::Get()
{
	if (GEngine)
	{
		return CastChecked<UGameUIGameUserSettings>(GEngine->GetGameUserSettings());
	}
	return nullptr;
}

FString UGameUIGameUserSettings::GetCurrentDifficulty() const
{
	return CurrentGameDifficulty;
}

void UGameUIGameUserSettings::SetCurrentDifficulty(const FString& InNewDifficulty)
{
	CurrentGameDifficulty = InNewDifficulty;
}

FString UGameUIGameUserSettings::GetCurrentLanguage() const
{
	return CurrentLanguage;
}

void UGameUIGameUserSettings::SetCurrentLanguage(const FString& InNewLanguage)
{
	FInternationalization::Get().SetCurrentLanguage(InNewLanguage);
	CurrentLanguage = InNewLanguage;
}

float UGameUIGameUserSettings::GetOverallVolume() const
{
	return OverallVolume;
}

void UGameUIGameUserSettings::SetOverallVolume(const float InOverallVolume)
{
	OverallVolume = InOverallVolume;
}

float UGameUIGameUserSettings::GetMusicVolume() const
{
	return MusicVolume;
}

void UGameUIGameUserSettings::SetMusicVolume(const float InMusicVolume)
{
	MusicVolume = InMusicVolume;
}

float UGameUIGameUserSettings::GetSoundFXVolume() const
{
	return SoundFXVolume;
}

void UGameUIGameUserSettings::SetSoundFXVolume(const float InMusicVolume)
{
	SoundFXVolume = InMusicVolume;
}

bool UGameUIGameUserSettings::GetAllowBackgroundAudio() const
{
	return AllowBackgroundAudio;
}

void UGameUIGameUserSettings::SetAllowBackgroundAudio(bool InAllowBackgroundAudio)
{
	AllowBackgroundAudio = InAllowBackgroundAudio;
}

bool UGameUIGameUserSettings::GetUseHDRAudio() const
{
	return UseHDRAudio;
}

void UGameUIGameUserSettings::SetUseHDRAudio(bool InUseHDRAudio)
{
	UseHDRAudio = InUseHDRAudio;
}

FString UGameUIGameUserSettings::GetWindowMode() const
{
	return UGameUIFunctionLibrary::EnumToString(GetFullscreenMode());
}

void UGameUIGameUserSettings::SetWindowMode(const FString& InWindowMode)
{
	WindowMode = InWindowMode;

	SetFullscreenMode(UGameUIFunctionLibrary::StringToEnum<EWindowMode::Type>(WindowMode));
}

float UGameUIGameUserSettings::GetCurrentDisplayGamma() const
{
	if (GEngine)
	{
		return GEngine->GetDisplayGamma();
	}
	return 0.f;
}

void UGameUIGameUserSettings::SetCurrentDisplayGamma(const float InDisplayGamma)
{
	if (GEngine)
	{
		GEngine->DisplayGamma = InDisplayGamma;
	}
}

void UGameUIGameUserSettings::LoadSettings(bool bForceReload)
{
	Super::LoadSettings(bForceReload);

	if (!CurrentLanguage.IsEmpty())
	{
		FInternationalization::Get().SetCurrentLanguage(CurrentLanguage);
	}
}
