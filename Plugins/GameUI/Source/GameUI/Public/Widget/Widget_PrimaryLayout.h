// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "Widget_PrimaryLayout.generated.h"

class UCommonActivatableWidgetContainerBase;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta=(DisableNativeTick))
class GAMEUI_API UWidget_PrimaryLayout : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="GameUI|PrimaryLayout")
	void RegisterWidgetStack(
		UPARAM(meta=(Categories ="GameUI.WidgetStack"))FGameplayTag InStackTag,
		UCommonActivatableWidgetContainerBase* InStack);

	UFUNCTION(BlueprintCallable, category="GameUI|PrimaryLayout")
	UCommonActivatableWidgetContainerBase* GetWidgetStackByTag(const FGameplayTag& InStackTag) const;

private:
	UPROPERTY(Transient)
	TMap<FGameplayTag, UCommonActivatableWidgetContainerBase*> RegisteredWidgetStackMap;
};
