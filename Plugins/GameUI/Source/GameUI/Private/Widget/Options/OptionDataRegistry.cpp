// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/OptionDataRegistry.h"
#include "Widget/Options/DataObject/ListDataObject_String.h"
#include "Widget/Options/DataObject/ListDataObject_Collection.h"

void UOptionDataRegistry::InitOptionDataRegistry(ULocalPlayer* InOwningLocalPlayer)
{
	InitGamePlayCollectionTab();
	InitAudioCollectionTab();
	InitVideoCollectionTab();
	InitControlCollectionTab();
}

const TArray<UListDataObject_Collection*>& UOptionDataRegistry::GetRegisteredOptionTabCollections() const
{
	return RegisteredOptionsTabCollections;
}

TArray<UListDataObject_Base*> UOptionDataRegistry::GetListSourceItemByTabId(const FName& InTabId) const
{
	UListDataObject_Collection* const* FoundTabCollectionPtr = RegisteredOptionsTabCollections.FindByPredicate(
		[InTabId](const UListDataObject_Collection* TabCollection)-> bool
		{
			return TabCollection->GetDataID() == InTabId;
		}
	);

	check(FoundTabCollectionPtr);

	const UListDataObject_Collection* FoundTabCollection = *FoundTabCollectionPtr;

	return FoundTabCollection->GetAllChildListData();
}

void UOptionDataRegistry::InitGamePlayCollectionTab()
{
	UListDataObject_Collection* GameplayTabCollection = NewObject<UListDataObject_Collection>();

	GameplayTabCollection->SetDataID(FName("GameplayTabCollection"));
	GameplayTabCollection->SetDataDisplayName(FText::FromString("Gameplay"));

	//GameDifficult
	{
		UListDataObject_String* GameDifficulty = NewObject<UListDataObject_String>();
		GameDifficulty->SetDataID(FName("GameDifficult"));
		GameDifficulty->SetDataDisplayName(FText::FromString("Difficult"));
		GameDifficulty->AddDynamicOptions(TEXT("Easy"), FText::FromString(TEXT("Easy")));
		GameDifficulty->AddDynamicOptions(TEXT("Normal"), FText::FromString(TEXT("Normal")));
		GameDifficulty->AddDynamicOptions(TEXT("Hard"), FText::FromString(TEXT("Hard")));
		GameDifficulty->AddDynamicOptions(TEXT("Nightmare"), FText::FromString(TEXT("Nightmare")));

		GameplayTabCollection->AddChildListData(GameDifficulty);
	}

	//Test Item
	{
		UListDataObject_String* TestItem = NewObject<UListDataObject_String>();
		TestItem->SetDataID(FName("TestItem"));
		TestItem->SetDataDisplayName(FText::FromString("TestItem"));

		GameplayTabCollection->AddChildListData(TestItem);
	}

	RegisteredOptionsTabCollections.Add(GameplayTabCollection);
}

void UOptionDataRegistry::InitAudioCollectionTab()
{
	UListDataObject_Collection* AudioTabCollection = NewObject<UListDataObject_Collection>();

	AudioTabCollection->SetDataID(FName("AudioTabCollection"));
	AudioTabCollection->SetDataDisplayName(FText::FromString("Audio"));

	RegisteredOptionsTabCollections.Add(AudioTabCollection);
}

void UOptionDataRegistry::InitVideoCollectionTab()
{
	UListDataObject_Collection* VideoTabCollection = NewObject<UListDataObject_Collection>();

	VideoTabCollection->SetDataID(FName("VideoTabCollection"));
	VideoTabCollection->SetDataDisplayName(FText::FromString("Video"));

	RegisteredOptionsTabCollections.Add(VideoTabCollection);
}

void UOptionDataRegistry::InitControlCollectionTab()
{
	UListDataObject_Collection* ControlTabCollection = NewObject<UListDataObject_Collection>();

	ControlTabCollection->SetDataID(FName("ControlTabCollection"));
	ControlTabCollection->SetDataDisplayName(FText::FromString("Control"));

	RegisteredOptionsTabCollections.Add(ControlTabCollection);
}
