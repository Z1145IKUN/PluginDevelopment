// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GameUITypes/GameUIEnums.h"
#include "AsyncAction_PushConfirmScreen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConfirmScreenButtonClickedDelegate,EConfirmScreenButtonType,ClickedButtonType);
/**
 * 
 */
UCLASS()
class GAMEUI_API UAsyncAction_PushConfirmScreen : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable,
		Category="GameUI|PushConfirmScreen",
		meta=(WorldContext="WorldContextObject",
			HidePin="WorldContextObject",
			Displayname="Show Confirm Screen",
			BlueprintInternalUseOnly="true"))
	static UAsyncAction_PushConfirmScreen* PushConfirmScreen(
		const UObject* WorldContextObject,
		EConfirmScreenType InConfirmScreenType,
		FText InScreenTitle,
		FText InScreenMessage);

	virtual void Activate() override;
	
	UPROPERTY(BlueprintAssignable,Category="GameUI|PushConfirmScreen")
	FOnConfirmScreenButtonClickedDelegate OnConfirmScreenButtonClicked;
	
private:
	TWeakObjectPtr<UWorld> CachedWorld;
	EConfirmScreenType CachedConfirmScreenType;
	FText CachedScreenTitle;
	FText CachedScreenMessage;
	
};
