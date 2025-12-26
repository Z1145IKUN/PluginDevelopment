// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Widget_ActivatableBase.h"
#include "GameUITypes/GameUIEnums.h"
#include "Widget_ConfirmScreen.generated.h"

class UCommonTextBlock;
class UDynamicEntryBox;

USTRUCT(BlueprintType)
struct FConfirmScreenButtonInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EConfirmScreenButtonType ConfirmScreenButtonType = EConfirmScreenButtonType::Unknown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ButtonTextToDisplay;
};

UCLASS()
class GAMEUI_API UConfirmScreenInfoObject : public UObject
{
	GENERATED_BODY()

public:
	static UConfirmScreenInfoObject* CreateOkScreen(const FText& InScreenTitle, const FText& InScreenMessage);
	static UConfirmScreenInfoObject* CreateYesNoScreen(const FText& InScreenTitle, const FText& InScreenMessage);
	static UConfirmScreenInfoObject* CreateOkCancelScreen(const FText& InScreenTitle, const FText& InScreenMessage);

	UPROPERTY(Transient)
	FText ConfirmScreenTitle;

	UPROPERTY(Transient)
	FText ConfirmScreenMessage;

	UPROPERTY(Transient)
	TArray<FConfirmScreenButtonInfo> AvailableScreenButtons;
};

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta=(DisableNativeTick))
class GAMEUI_API UWidget_ConfirmScreen : public UWidget_ActivatableBase
{
	GENERATED_BODY()

public:
	void InitConfirmScreen(
		UConfirmScreenInfoObject* InScreenInfoObject,
		TFunction<void(EConfirmScreenButtonType)> ClickedButtonCallBack);

private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_Title;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_Message;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UDynamicEntryBox> DynamicEntryBox_Buttons;
};
