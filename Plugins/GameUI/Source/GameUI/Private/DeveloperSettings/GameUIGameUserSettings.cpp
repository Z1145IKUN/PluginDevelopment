// Fill out your copyright notice in the Description page of Project Settings.


#include "DeveloperSettings/GameUIGameUserSettings.h"

UGameUIGameUserSettings::UGameUIGameUserSettings()
{
	OverallVolume = 1.f;
	MusicVolume = 1.f;
	SoundFXVolume = 1.f;
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
