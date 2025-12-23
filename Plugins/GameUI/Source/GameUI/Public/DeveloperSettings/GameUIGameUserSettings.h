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
	static UGameUIGameUserSettings* Get();

	//***** Gameplay Collection Tab *****//
	UFUNCTION()
	FString GetCurrentDifficulty() const;
	UFUNCTION()
	void SetCurrentDifficulty(const FString& InNewDifficulty);
	//***** Gameplay Collection Tab *****//

private:
	UPROPERTY(Config)
	FString CurrentGameDifficulty;
};
