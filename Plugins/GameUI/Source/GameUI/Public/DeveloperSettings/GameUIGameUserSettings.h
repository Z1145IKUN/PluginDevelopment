// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "GameUIGameUserSettings.generated.h"

/**
 * 
 */
UCLASS()
class GAMEUI_API UGameUIGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	UGameUIGameUserSettings();

	static UGameUIGameUserSettings* Get();

	//***** Gameplay Collection Tab *****//
	UFUNCTION()
	FString GetCurrentDifficulty() const;
	UFUNCTION()
	void SetCurrentDifficulty(const FString& InNewDifficulty);

	UFUNCTION()
	FString GetCurrentLanguage() const;
	UFUNCTION()
	void SetCurrentLanguage(const FString& InNewLanguage);
	//***** Gameplay Collection Tab *****//

	//***** Audio Collection Tab *****//
	UFUNCTION()
	float GetOverallVolume() const;
	UFUNCTION()
	void SetOverallVolume(const float InOverallVolume);

	UFUNCTION()
	float GetMusicVolume() const;
	UFUNCTION()
	void SetMusicVolume(const float InMusicVolume);

	UFUNCTION()
	float GetSoundFXVolume() const;
	UFUNCTION()
	void SetSoundFXVolume(const float InMusicVolume);

	UFUNCTION()
	bool GetAllowBackgroundAudio() const;
	UFUNCTION()
	void SetAllowBackgroundAudio(bool InAllowBackgroundAudio);

	UFUNCTION()
	bool GetUseHDRAudio() const;
	UFUNCTION()
	void SetUseHDRAudio(bool InUseHDRAudio);
	//***** Audio Collection Tab *****//

	//***** Video Collection Tab *****//
	UFUNCTION()
	FString GetWindowMode() const;
	UFUNCTION()
	void SetWindowMode(const FString& InWindowMode);

	UFUNCTION()
	float GetCurrentDisplayGamma() const;
	UFUNCTION()
	void SetCurrentDisplayGamma(const float InDisplayGamma);
	//***** Video Collection Tab *****//

private:
	//***** Gameplay Collection Tab *****//
	UPROPERTY(Config)
	FString CurrentGameDifficulty;

	UPROPERTY(Config)
	FString CurrentLanguage;
	//***** Gameplay Collection Tab *****//

	//***** Audio Collection Tab *****//
	UPROPERTY(Config)
	float OverallVolume;

	UPROPERTY(Config)
	float MusicVolume;

	UPROPERTY(Config)
	float SoundFXVolume;

	UPROPERTY(Config)
	bool AllowBackgroundAudio;

	UPROPERTY(Config)
	bool UseHDRAudio;
	//***** Audio Collection Tab *****//

	//***** Video Collection Tab *****//
	UPROPERTY(config)
	FString WindowMode;
	//***** Video Collection Tab *****//

	virtual void LoadSettings(bool bForceReload = false) override;
};
