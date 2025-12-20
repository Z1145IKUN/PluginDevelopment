// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/Widget_OptionScreen.h"

#include "ICommonInputModule.h"
#include "Input/CommonUIInputTypes.h"
#include "Widget/Options/OptionDataRegistry.h"
#include "Widget/Options/Widget_TabListWidgetBase.h"
#include "Widget/Options/DataObject/ListDataObject_Collection.h"

void UWidget_OptionScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!ResetAction.IsNull())
	{
		ResetAction_Handle = RegisterUIActionBinding(
			FBindUIActionArgs(
				ResetAction,
				true,
				FSimpleDelegate::CreateUObject(
					this,
					&ThisClass::OnResetActionTriggered
				)
			)
		);
	}

	RegisterUIActionBinding(
		FBindUIActionArgs(
			ICommonInputModule::GetSettings().GetDefaultBackAction(),
			true,
			FSimpleDelegate::CreateUObject(
				this,
				&ThisClass::OnBackActionTriggered
			)
		)
	);

	TabListWidget_OptionsTab->OnTabSelected.AddUniqueDynamic(this, &ThisClass::OnOptionsTabSelected);
}

void UWidget_OptionScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	for (const UListDataObject_Collection* TabCollection : GetOrCreateOptionDataRegistry()->
	     GetRegisteredOptionTabCollections())
	{
		if (!TabCollection)
		{
			continue;
		}

		const FName TabID = TabCollection->GetDataID();
		if (TabListWidget_OptionsTab->GetTabButtonBaseByID(TabID) != nullptr)
		{
			continue;
		}

		TabListWidget_OptionsTab->RequestRegisterTab(TabID, TabCollection->GetDataDisplayName());
	}
}

void UWidget_OptionScreen::OnResetActionTriggered()
{
}

void UWidget_OptionScreen::OnBackActionTriggered()
{
	DeactivateWidget();
}

void UWidget_OptionScreen::OnOptionsTabSelected(FName TabID)
{
}

UOptionDataRegistry* UWidget_OptionScreen::GetOrCreateOptionDataRegistry()
{
	if (!OwningOptionDataRegistry)
	{
		OwningOptionDataRegistry = NewObject<UOptionDataRegistry>();
		OwningOptionDataRegistry->InitOptionDataRegistry(GetOwningLocalPlayer());
	}

	check(OwningOptionDataRegistry);

	return OwningOptionDataRegistry;
}
