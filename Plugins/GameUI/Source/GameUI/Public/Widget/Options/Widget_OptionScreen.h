// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Widget_ActivatableBase.h"
#include "Widget_OptionScreen.generated.h"

class UOptionDataRegistry;
class UWidget_TabListWidgetBase;
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

	//~ Begin UCommonActivatableWidget interface
	virtual void NativeOnActivated() override;
	//~ End UCommonActivatableWidget Interface

private:
	void OnResetActionTriggered();
	void OnBackActionTriggered();

	UOptionDataRegistry* GetOrCreateOptionDataRegistry();

	//***** Bound Widget *****//
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UWidget_TabListWidgetBase> TabListWidget_OptionsTab;


	// reset action data table handle
	UPROPERTY(EditDefaultsOnly,
		Category = "GameUI|OptionScreen",
		meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;

	//Reset binding action handle
	FUIActionBindingHandle ResetAction_Handle;

	//Handle the creation operation of data in the option Screen. Direct access to this variable is forbidden.
	UPROPERTY(Transient)
	TObjectPtr<UOptionDataRegistry> OwningOptionDataRegistry;
};
