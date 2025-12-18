// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameUISubsystem.generated.h"


class UWidget_PrimaryLayout;
/**
 * 
 */
UCLASS()
class GAMEUI_API UGameUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UGameUISubsystem* Get(const UObject* WorldContextObject);

	//~ Begin USubsystem
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	//~ End USubsystem

	UFUNCTION(BlueprintCallable, Category="GameUI|GameUISubsystem")
	void RegisterPrimaryLayout(UWidget_PrimaryLayout* InPrimaryLayout);

private:
	UPROPERTY(Transient)
	TObjectPtr<UWidget_PrimaryLayout> CreatedPrimaryLayout;
};
