// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Widget_ActivatableBase.h"
#include "Game/GameUIPlayerController.h"

bool UWidget_ActivatableBase::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	SetIsFocusable(true);
	SetVisibility(ESlateVisibility::Visible);
	return true;
}

AGameUIPlayerController* UWidget_ActivatableBase::GetGameUIPlayerController()
{
	if (!CachedGameUIPlayerController.IsValid())
	{
		CachedGameUIPlayerController = GetOwningPlayer<AGameUIPlayerController>();
	}

	return CachedGameUIPlayerController.IsValid() ? CachedGameUIPlayerController.Get() : nullptr;
}
