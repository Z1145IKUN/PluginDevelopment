// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncAction/AsyncAction_PushSoftWidget.h"
#include "Subsystem/GameUISubsystem.h"
#include "Widget/Widget_ActivatableBase.h"

UAsyncAction_PushSoftWidget* UAsyncAction_PushSoftWidget::PushSoftWidget(
	const UObject* WorldContextObject,
	APlayerController* OwningPlayerController,
	TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,
	FGameplayTag InStackTag,
	bool bFocusOnNewlyPushWidget)
{
	check(!InSoftWidgetClass.IsNull())

	if (GEngine)
	{
		if (UWorld* World = GEngine->
			GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			UAsyncAction_PushSoftWidget* Node = NewObject<UAsyncAction_PushSoftWidget>();
			Node->CachedWorld = World;
			Node->CachedOwningPlayerController = OwningPlayerController;
			Node->CachedSoftWidgetClass = InSoftWidgetClass;
			Node->CachedWidgetStackTag = InStackTag;
			Node->bCachedFocusOnNewlyPushWidget = bFocusOnNewlyPushWidget;

			Node->RegisterWithGameInstance(World);

			return Node;
		}
	}

	return nullptr;
}

void UAsyncAction_PushSoftWidget::Activate()
{
	Super::Activate();

	UGameUISubsystem* FrontEndUISubsystem = UGameUISubsystem::Get(CachedWorld.Get());

	FrontEndUISubsystem->PushSoftWidgetToStack(
		CachedWidgetStackTag,
		CachedSoftWidgetClass,
		[this](EAsyncPushWidgetState InPushState, UWidget_ActivatableBase* PushedWidget)
		{
			switch (InPushState)
			{
			case EAsyncPushWidgetState::OnCreatedBeforePush:
				PushedWidget->SetOwningPlayer(CachedOwningPlayerController.Get());
				OnWidgetCreatedBeforePush.Broadcast(PushedWidget);
				break;
			case EAsyncPushWidgetState::AfterPush:
				AfterPush.Broadcast(PushedWidget);
				if (bCachedFocusOnNewlyPushWidget)
				{
					if (UWidget* WidgetToFocus = PushedWidget->GetDesiredFocusTarget())
					{
						WidgetToFocus->SetFocus();
					}
				}
				SetReadyToDestroy();
				break;
			default:
				break;
			}
		}
	);
}
