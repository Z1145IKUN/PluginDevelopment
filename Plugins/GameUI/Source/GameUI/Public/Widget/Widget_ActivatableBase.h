// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Widget_ActivatableBase.generated.h"

class AGameUIPlayerController;
/**
 * 
 */
UCLASS(Abstract,BlueprintType,meta=(DisableNativeTick))
class GAMEUI_API UWidget_ActivatableBase : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:
	//~ Begin UUserWidget interface
	virtual bool Initialize() override;
	//~ End UUserWidget interface
	
	UFUNCTION(BlueprintPure,Category="GameUI|ActivatableBase")
	AGameUIPlayerController* GetGameUIPlayerController();
	
private:
	TWeakObjectPtr<AGameUIPlayerController> CachedGameUIPlayerController;
};
