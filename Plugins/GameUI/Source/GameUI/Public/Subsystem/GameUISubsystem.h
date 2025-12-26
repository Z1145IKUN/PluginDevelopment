// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameUITypes/GameUIEnums.h"
#include "GameUISubsystem.generated.h"

class UWidget_PrimaryLayout;
class UWidget_ActivatableBase;
class UGameUIButtonBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnButtonDescriptionTextUpdateDelegate,
	UGameUIButtonBase*, UpdatedButton,
	FText, ButtonDescriptionText);

enum class EAsyncPushWidgetState : uint8
{
	OnCreatedBeforePush,
	AfterPush
};
/**
 * 
 */
UCLASS()
class GAMEUI_API UGameUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UGameUISubsystem* Get(const UObject* WorldContextObject);

	//~ Begin USubsystem
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	//~ End USubsystem

	UFUNCTION(BlueprintCallable, Category="GameUI|GameUISubsystem")
	void RegisterPrimaryLayout(UWidget_PrimaryLayout* InPrimaryLayout);

	void PushSoftWidgetToStack(
		const FGameplayTag& InStackTag,
		TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,
		TFunction<void(EAsyncPushWidgetState, UWidget_ActivatableBase*)> AsyncPushStateCallBack);
	
	UPROPERTY(BlueprintAssignable,Category="GameUI|GameUISubsystem")
	FOnButtonDescriptionTextUpdateDelegate OnDescriptionTextUpdate;
	
	void PushConfirmScreenToModalStackAsync(
		EConfirmScreenType InScreenType,
		const FText& InScreenTitle,
		const FText& InScreenMessage,
		TFunction<void(EConfirmScreenButtonType)> ScreenButtonCallBack);

private:
	UPROPERTY(Transient)
	TObjectPtr<UWidget_PrimaryLayout> CreatedPrimaryLayout;
};
