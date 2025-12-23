// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_OptionDetailsView.generated.h"

class UCommonTextBlock;
class UCommonLazyImage;
class UCommonRichTextBlock;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta=(DisableNativeTick))
class GAMEUI_API UWidget_OptionDetailsView : public UUserWidget
{
	GENERATED_BODY()

private:
	//***** Bound Widget *****//
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_Title;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonLazyImage> CommonLazyImage_DescriptionImage;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonRichTextBlock> CommonRichTextBlock_Description;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonRichTextBlock> CommonRichTextBlock_DynamicDetails;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonRichTextBlock> CommonRichTextBlock_DisabledReason;
	//***** Bound Widget *****//
};
