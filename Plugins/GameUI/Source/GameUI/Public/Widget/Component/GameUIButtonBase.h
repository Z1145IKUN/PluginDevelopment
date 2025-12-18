// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "GameUIButtonBase.generated.h"

class UCommonTextBlock;
/**
 * 
 */
UCLASS(Abstract,BlueprintType,meta=(DisableNativeTick))
class GAMEUI_API UGameUIButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()
	
public:
	//~ Begin UUserWidget Interface
	virtual void NativePreConstruct() override;
	//~ End UUserWidget Interface
	
	//~ Begin UCommonButtonBase Interface
	virtual void NativeOnCurrentTextStyleChanged() override;
	//~ End UCommonButtonBase Interface
	
	UFUNCTION(BlueprintCallable)
	void SetButtonText(FText InButtonText);

private:
	//***** Bind widget *****//
	UPROPERTY(meta=(BindWidgetOptional))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_ButtonText;
	//***** Bind widget *****//

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameUI|Button", meta=(AllowPrivateAccess="true"))
	FText ButtonDisplayText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameUI|Button", meta=(AllowPrivateAccess="true"))
	bool bUseUpperCaseForButtonText = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameUI|Button", meta=(AllowPrivateAccess="true"))
	FText ButtonDescriptionText;
};
