// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Widget_ActivatableBase.h"
#include "Game/GameUIPlayerController.h"

AGameUIPlayerController* UWidget_ActivatableBase::GetGameUIPlayerController()
{
	if (!CachedGameUIPlayerController.IsValid())
	{
		CachedGameUIPlayerController = GetOwningPlayer<AGameUIPlayerController>();
	}

	return CachedGameUIPlayerController.IsValid() ? CachedGameUIPlayerController.Get() : nullptr;
}
