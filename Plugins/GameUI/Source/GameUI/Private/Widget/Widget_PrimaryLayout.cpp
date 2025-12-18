// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Widget_PrimaryLayout.h"

void UWidget_PrimaryLayout::RegisterWidgetStack(FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* InStack)
{
	check(InStack)

	if (!IsDesignTime())
	{
		if (!RegisteredWidgetStackMap.Contains(InStackTag))
		{
			RegisteredWidgetStackMap.Add(InStackTag, InStack);
		}
	}
}

UCommonActivatableWidgetContainerBase* UWidget_PrimaryLayout::GetWidgetStackByTag(const FGameplayTag& InStackTag) const
{
	check(RegisteredWidgetStackMap.Contains(InStackTag))

	return RegisteredWidgetStackMap.FindRef(InStackTag);
}
