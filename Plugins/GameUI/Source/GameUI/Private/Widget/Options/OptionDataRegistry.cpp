// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/OptionDataRegistry.h"

#include "GameUIGameplayTags.h"
#include "DeveloperSettings/GameUIGameUserSettings.h"
#include "FunctionLibrary/GameUIFunctionLibrary.h"
#include "Widget/Options/OptionsDataInteractionHelper.h"
#include "Widget/Options/DataObject/ListDataObject_String.h"
#include "Widget/Options/DataObject/ListDataObject_Collection.h"

#define MAKE_DATA_OPTION_CONTROL(GetterOrSetterFuncName) \
	MakeShared<FOptionsDataInteractionHelper> \
	(GET_FUNCTION_NAME_STRING_CHECKED(UGameUIGameUserSettings, GetterOrSetterFuncName))

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

	TArray<UListDataObject_Base*> AllChildListItems;

	for (UListDataObject_Base* ChildListData : FoundTabCollection->GetAllChildListData())
	{
		if (!ChildListData) continue;

		AllChildListItems.Add(ChildListData);

		if (ChildListData->HasChildListData())
		{
			FindChildListDataRecursively(ChildListData, AllChildListItems);
		}
	}

	return AllChildListItems;
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
		GameDifficulty->SetDefaultValueFromString(TEXT("Normal"));
		GameDifficulty->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetCurrentDifficulty));
		GameDifficulty->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetCurrentDifficulty));
		GameDifficulty->SetShouldApplySettingsImmediately(true);
		GameDifficulty->SetDescriptionRichText(
			FText::FromString(
				TEXT(
					"The game allows you to adjust the difficulty at any time. \n\n"
					"<Bold>Easy</> \n\n"
					"<Bold>Normal</>\n\n"
					"<Bold>Hard</>\n\n"
					"<Bold>Nightmare</>"
				)
			)
		);
		GameplayTabCollection->AddChildListData(GameDifficulty);
	}

	//Test Item
	{
		UListDataObject_String* TestItem = NewObject<UListDataObject_String>();
		TestItem->SetDataID(FName("TestItem"));
		TestItem->SetDataDisplayName(FText::FromString("TestItem"));
		TestItem->SetSoftDescriptionImage(
			UGameUIFunctionLibrary::GetSoftImageByTag(GameUIGameplayTags::GameUI_Image_TestImage));

		GameplayTabCollection->AddChildListData(TestItem);
	}

	RegisteredOptionsTabCollections.Add(GameplayTabCollection);
}

void UOptionDataRegistry::InitAudioCollectionTab()
{
	UListDataObject_Collection* AudioTabCollection = NewObject<UListDataObject_Collection>();

	AudioTabCollection->SetDataID(FName("AudioTabCollection"));
	AudioTabCollection->SetDataDisplayName(FText::FromString("Audio"));

	//Volume Category
	{
		UListDataObject_Collection* VolumeCategoryCollection = NewObject<UListDataObject_Collection>();
		VolumeCategoryCollection->SetDataID(FName("VolumeCategoryCollection"));
		VolumeCategoryCollection->SetDataDisplayName(FText::FromString("Volume"));

		//Test Item
		{
			UListDataObject_String* TestItem = NewObject<UListDataObject_String>();
			TestItem->SetDataID(FName("TestItem"));
			TestItem->SetDataDisplayName(FText::FromString("TestItem"));

			VolumeCategoryCollection->AddChildListData(TestItem);
		}

		AudioTabCollection->AddChildListData(VolumeCategoryCollection);
	}

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

void UOptionDataRegistry::FindChildListDataRecursively(const UListDataObject_Base* InParentListData,
                                                       TArray<UListDataObject_Base*>& OutFoundChildListDataArray) const
{
	if (!InParentListData || !InParentListData->HasChildListData())
	{
		return;
	}

	for (UListDataObject_Base* ChildListData : InParentListData->GetAllChildListData())
	{
		if (!ChildListData) continue;

		OutFoundChildListDataArray.Add(ChildListData);

		if (ChildListData->HasChildListData())
		{
			FindChildListDataRecursively(ChildListData, OutFoundChildListDataArray);
		}
	}
}
