// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/Widget_OptionScreen.h"

#include "ICommonInputModule.h"
#include "DeveloperSettings/GameUIGameUserSettings.h"
#include "Input/CommonUIInputTypes.h"
#include "Widget/Component/GameUIListView.h"
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
	ListView_OptionsList->OnItemIsHoveredChanged().AddUObject(this, &ThisClass::OnListViewItemHoveredChanged);
	ListView_OptionsList->OnItemSelectionChanged().AddUObject(this, &ThisClass::OnListViewItemSelectedChanged);
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

void UWidget_OptionScreen::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	UGameUIGameUserSettings::Get()->ApplySettings(true);
}

void UWidget_OptionScreen::OnResetActionTriggered()
{
}

void UWidget_OptionScreen::OnBackActionTriggered()
{
	DeactivateWidget();
}

void UWidget_OptionScreen::OnListViewItemHoveredChanged(UObject* InHoveredItem, bool bWasHovered)
{
	if (!InHoveredItem)
	{
		return;
	}
}

void UWidget_OptionScreen::OnListViewItemSelectedChanged(UObject* InSelectedItem)
{
	if (!InSelectedItem)
	{
		return;
	}
}

void UWidget_OptionScreen::OnOptionsTabSelected(FName TabID)
{
	TArray<UListDataObject_Base*> FoundListSourceItem = GetOrCreateOptionDataRegistry()->
		GetListSourceItemByTabId(TabID);

	ListView_OptionsList->SetListItems<UListDataObject_Base*>(FoundListSourceItem);
	ListView_OptionsList->RequestRefresh();

	if (ListView_OptionsList->GetNumItems() != 0)
	{
		ListView_OptionsList->NavigateToIndex(0);
		ListView_OptionsList->SetSelectedIndex(0);
	}
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
