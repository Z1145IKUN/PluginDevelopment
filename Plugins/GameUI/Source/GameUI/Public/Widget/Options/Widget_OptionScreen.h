// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Widget_ActivatableBase.h"
#include "Widget_OptionScreen.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta=(DisableNativeTick))
class GAMEUI_API UWidget_OptionScreen : public UWidget_ActivatableBase
{
	GENERATED_BODY()
	
protected:
	// ~Begin UUserWidget interface
	virtual void NativeOnInitialized() override;
	// ~End UUserWidget interface
	
private:
	void OnResetActionTriggered();
	void OnBackActionTriggered();
	
	UPROPERTY(EditDefaultsOnly,
		Category = "GameUI|OptionScreen", 
		meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;
	
	FUIActionBindingHandle ResetAction_Handle;
	
};
