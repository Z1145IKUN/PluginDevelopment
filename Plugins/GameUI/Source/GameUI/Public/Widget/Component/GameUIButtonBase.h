// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "GameUIButtonBase.generated.h"

class UCommonTextBlock;
class UCommonLazyImage;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta=(DisableNativeTick))
class GAMEUI_API UGameUIButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	//~ Begin UUserWidget Interface
	virtual void NativePreConstruct() override;
	//~ End UUserWidget Interface

	//~ Begin UCommonButtonBase Interface
	virtual void NativeOnCurrentTextStyleChanged() override;
	virtual void NativeOnHovered() override;
	virtual void NativeOnUnhovered() override;
	//~ End UCommonButtonBase Interface

	UFUNCTION(BlueprintCallable)
	void SetButtonText(FText InButtonText);

	UFUNCTION(BlueprintCallable)
	FText GetButtonDisplayText() const;

	UFUNCTION(BlueprintCallable)
	void SetButtonImage(const FSlateBrush& InBrush);

private:
	//***** Bind widget *****//
	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional, AllowPrivateAccess="true"))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_ButtonText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional, AllowPrivateAccess="true"))
	TObjectPtr<UCommonLazyImage> CommonLazyImage_ButtonImage;
	//***** Bind widget *****//

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameUI|Button", meta=(AllowPrivateAccess="true"))
	FText ButtonDisplayText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameUI|Button", meta=(AllowPrivateAccess="true"))
	bool bUseUpperCaseForButtonText = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameUI|Button", meta=(AllowPrivateAccess="true"))
	FText ButtonDescriptionText;
};
