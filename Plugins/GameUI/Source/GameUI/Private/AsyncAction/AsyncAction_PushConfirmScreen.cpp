// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncAction/AsyncAction_PushConfirmScreen.h"

#include "Subsystem/GameUISubsystem.h"

UAsyncAction_PushConfirmScreen* UAsyncAction_PushConfirmScreen::PushConfirmScreen(
	const UObject* WorldContextObject,
	EConfirmScreenType InConfirmScreenType, FText InScreenTitle, FText InScreenMessage)
{
	if (GEngine)
	{
		if (UWorld* World = GEngine->
			GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			UAsyncAction_PushConfirmScreen* Node = NewObject<UAsyncAction_PushConfirmScreen>();
			Node->CachedWorld = World;
			Node->CachedConfirmScreenType = InConfirmScreenType;
			Node->CachedScreenTitle = InScreenTitle;
			Node->CachedScreenMessage = InScreenMessage;

			Node->RegisterWithGameInstance(World);
			return Node;
		}
	}
	return nullptr;
}

void UAsyncAction_PushConfirmScreen::Activate()
{
	Super::Activate();

	UGameUISubsystem::Get(CachedWorld.Get())->PushConfirmScreenToModalStackAsync(
		CachedConfirmScreenType,
		CachedScreenTitle,
		CachedScreenMessage,
		[this](EConfirmScreenButtonType ClickedButtonType)
		{
			OnConfirmScreenButtonClicked.Broadcast(ClickedButtonType);
			SetReadyToDestroy();
		}
	);
}
