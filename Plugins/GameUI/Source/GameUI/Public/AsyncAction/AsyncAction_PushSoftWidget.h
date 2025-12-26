// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncAction_PushSoftWidget.generated.h"

class UWidget_ActivatableBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPushSoftWidgetDelegate,UWidget_ActivatableBase*,PushedWidget);
/**
 * 
 */
UCLASS()
class GAMEUI_API UAsyncAction_PushSoftWidget : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,
		Category="GameUI|AsyncAction",
		meta=(WorldContext="WorldContextObject",
			HidePin="WorldContextObject",
			DisplayName="Push Soft Widget To Stack",
			BlueprintInternalUseOnly="true"))
	static UAsyncAction_PushSoftWidget* PushSoftWidget(
		const UObject* WorldContextObject,
		APlayerController* OwningPlayerController,
		TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,
		UPARAM(meta=(Categories = "GameUI.WidgetStack"))
		FGameplayTag InStackTag,
		bool bFocusOnNewlyPushWidget = true);
	
	//~ Begin UBlueprintAsyncActionBase Interface
	virtual void Activate() override;
	//~ End UBlueprintAsyncActionBase Interface
	
	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate OnWidgetCreatedBeforePush;

	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate AfterPush;
	
private:
	TWeakObjectPtr<UWorld> CachedWorld;
	TWeakObjectPtr<APlayerController> CachedOwningPlayerController;
	TSoftClassPtr<UWidget_ActivatableBase> CachedSoftWidgetClass;
	FGameplayTag CachedWidgetStackTag;
	bool bCachedFocusOnNewlyPushWidget = false;
};
