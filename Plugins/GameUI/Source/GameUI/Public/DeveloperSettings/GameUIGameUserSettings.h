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
	//***** Audio Collection Tab *****//

private:
	//***** Gameplay Collection Tab *****//
	UPROPERTY(Config)
	FString CurrentGameDifficulty;
	//***** Gameplay Collection Tab *****//

	//***** Audio Collection Tab *****//
	UPROPERTY(Config)
	float OverallVolume;

	UPROPERTY(Config)
	float MusicVolume;
	//***** Audio Collection Tab *****//
};
