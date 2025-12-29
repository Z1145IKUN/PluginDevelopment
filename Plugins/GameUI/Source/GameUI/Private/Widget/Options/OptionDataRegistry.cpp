// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/OptionDataRegistry.h"

// #include "GameUIGameplayTags.h"
#include "DeveloperSettings/GameUIGameUserSettings.h"
// #include "FunctionLibrary/GameUIFunctionLibrary.h"
#include "Widget/Options/OptionsDataInteractionHelper.h"
#include "Widget/Options/DataObject/ListDataObject_String.h"
#include "Widget/Options/DataObject/ListDataObject_Collection.h"
#include "Widget/Options/DataObject/ListDataObject_Scalar.h"
#include "Widget/Options/DataObject/ListDataObject_StringResolution.h"

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

	// //Test Item
	// {
	// 	UListDataObject_String* TestItem = NewObject<UListDataObject_String>();
	// 	TestItem->SetDataID(FName("TestItem"));
	// 	TestItem->SetDataDisplayName(FText::FromString("TestItem"));
	// 	TestItem->SetSoftDescriptionImage(
	// 		UGameUIFunctionLibrary::GetSoftImageByTag(GameUIGameplayTags::GameUI_Image_TestImage));
	//
	// 	GameplayTabCollection->AddChildListData(TestItem);
	// }

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

		//overall volume
		{
			UListDataObject_Scalar* OverallVolume = NewObject<UListDataObject_Scalar>();
			OverallVolume->SetDataID(FName("OverallVolume"));
			OverallVolume->SetDataDisplayName(FText::FromString(TEXT("Overall Volume")));
			OverallVolume->SetDescriptionRichText(FText::FromString(TEXT("This is description for overall volume")));
			OverallVolume->SetDisplayValueRange(TRange<float>(0.0f, 1.0f));
			OverallVolume->SetOutputValueRange(TRange<float>(0.0f, 2.0f));
			OverallVolume->SetSliderStepSize(0.01f);
			OverallVolume->SetDefaultValueFromString(LexToString(1.f));
			OverallVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
			OverallVolume->SetNumberFormattingOptions(UListDataObject_Scalar::NoDecimal());
			OverallVolume->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetOverallVolume));
			OverallVolume->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetOverallVolume));
			OverallVolume->SetShouldApplySettingsImmediately(true);

			VolumeCategoryCollection->AddChildListData(OverallVolume);
		}

		//Music volume
		{
			UListDataObject_Scalar* MusicVolume = NewObject<UListDataObject_Scalar>();
			MusicVolume->SetDataID(FName("MusicVolume"));
			MusicVolume->SetDataDisplayName(FText::FromString(TEXT("Music Volume")));
			MusicVolume->SetDescriptionRichText(FText::FromString(TEXT("This is description for Music volume")));
			MusicVolume->SetDisplayValueRange(TRange<float>(0.0f, 1.0f));
			MusicVolume->SetOutputValueRange(TRange<float>(0.0f, 2.0f));
			MusicVolume->SetSliderStepSize(0.01f);
			MusicVolume->SetDefaultValueFromString(LexToString(1.f));
			MusicVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
			MusicVolume->SetNumberFormattingOptions(UListDataObject_Scalar::NoDecimal());
			MusicVolume->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetMusicVolume));
			MusicVolume->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetMusicVolume));
			MusicVolume->SetShouldApplySettingsImmediately(true);

			VolumeCategoryCollection->AddChildListData(MusicVolume);
		}

		//Sound FX volume
		{
			UListDataObject_Scalar* SoundFXVolume = NewObject<UListDataObject_Scalar>();
			SoundFXVolume->SetDataID(FName("SoundFXVolume"));
			SoundFXVolume->SetDataDisplayName(FText::FromString(TEXT("Sound Effects Volume")));
			SoundFXVolume->SetDescriptionRichText(
				FText::FromString(TEXT("This is description for Sound Effects volume")));
			SoundFXVolume->SetDisplayValueRange(TRange<float>(0.0f, 1.0f));
			SoundFXVolume->SetOutputValueRange(TRange<float>(0.0f, 2.0f));
			SoundFXVolume->SetSliderStepSize(0.01f);
			SoundFXVolume->SetDefaultValueFromString(LexToString(1.f));
			SoundFXVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
			SoundFXVolume->SetNumberFormattingOptions(UListDataObject_Scalar::NoDecimal());
			SoundFXVolume->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetSoundFXVolume));
			SoundFXVolume->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetSoundFXVolume));
			SoundFXVolume->SetShouldApplySettingsImmediately(true);

			VolumeCategoryCollection->AddChildListData(SoundFXVolume);
		}

		AudioTabCollection->AddChildListData(VolumeCategoryCollection);
	}

	//Sound Category
	{
		UListDataObject_Collection* SoundCategory = NewObject<UListDataObject_Collection>();
		SoundCategory->SetDataID(FName("SoundCategory"));
		SoundCategory->SetDataDisplayName(FText::FromString(TEXT("Sound")));

		//Allow Background Audio
		{
			UListDataObject_StringBool* AllowBackgroundAudio = NewObject<UListDataObject_StringBool>();
			AllowBackgroundAudio->SetDataID(FName("AllowBackgroundAudio"));
			AllowBackgroundAudio->SetDataDisplayName(FText::FromString(TEXT("Allow Background Audio")));
			AllowBackgroundAudio->
				SetDescriptionRichText(FText::FromString(TEXT("Turn on or off the background Audio")));
			AllowBackgroundAudio->OverrideTrueDisplayText(FText::FromString(TEXT("Enable")));
			AllowBackgroundAudio->OverrideFalseDisplayText(FText::FromString(TEXT("Disable")));
			AllowBackgroundAudio->SetTrueAsDefaultString();
			AllowBackgroundAudio->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetAllowBackgroundAudio));
			AllowBackgroundAudio->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetAllowBackgroundAudio));
			AllowBackgroundAudio->SetShouldApplySettingsImmediately(true);

			SoundCategory->AddChildListData(AllowBackgroundAudio);
		}

		//Use HDR Audio
		{
			UListDataObject_StringBool* UseHDRAudio = NewObject<UListDataObject_StringBool>();
			UseHDRAudio->SetDataID(FName("UseHDRAudio"));
			UseHDRAudio->SetDataDisplayName(FText::FromString(TEXT("Use HDR Audio")));
			UseHDRAudio->
				SetDescriptionRichText(FText::FromString(TEXT("Turn on or off the HDR Audio")));
			UseHDRAudio->OverrideTrueDisplayText(FText::FromString(TEXT("Enable")));
			UseHDRAudio->OverrideFalseDisplayText(FText::FromString(TEXT("Disable")));
			UseHDRAudio->SetTrueAsDefaultString();
			UseHDRAudio->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetUseHDRAudio));
			UseHDRAudio->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetUseHDRAudio));
			UseHDRAudio->SetShouldApplySettingsImmediately(true);

			SoundCategory->AddChildListData(UseHDRAudio);
		}

		AudioTabCollection->AddChildListData(SoundCategory);
	}

	RegisteredOptionsTabCollections.Add(AudioTabCollection);
}

void UOptionDataRegistry::InitVideoCollectionTab()
{
	UListDataObject_Collection* VideoTabCollection = NewObject<UListDataObject_Collection>();

	VideoTabCollection->SetDataID(FName("VideoTabCollection"));
	VideoTabCollection->SetDataDisplayName(FText::FromString("Video"));

	// Display Category Collection 
	{
		UListDataObject_Collection* DisplayCategoryCollection = NewObject<UListDataObject_Collection>();
		DisplayCategoryCollection->SetDataID(FName("DisplayCategoryCollection"));
		DisplayCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Display")));

		//Window mode
		{
			UListDataObject_StringEnum* WindowMode = NewObject<UListDataObject_StringEnum>();
			WindowMode->SetDataID(FName("WindowMode"));
			WindowMode->SetDataDisplayName(FText::FromString(TEXT("Window Mode")));
			WindowMode->SetDescriptionRichText(FText::FromString(TEXT("Adjust the window mode")));
			WindowMode->AddEnumOption(EWindowMode::Fullscreen, FText::FromString(TEXT("Fullscreen")));
			WindowMode->AddEnumOption(EWindowMode::WindowedFullscreen, FText::FromString(TEXT("Borderless Window")));
			WindowMode->AddEnumOption(EWindowMode::Windowed, FText::FromString(TEXT("Windowed")));
			WindowMode->SetDefaultValueFromEnumOption(EWindowMode::WindowedFullscreen);
			WindowMode->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetFullscreenMode));
			WindowMode->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetFullscreenMode));
			WindowMode->SetShouldApplySettingsImmediately(true);

			DisplayCategoryCollection->AddChildListData(WindowMode);
		}

		//Screen Resolution
		{
			UListDataObject_StringResolution* ScreenResolution = NewObject<UListDataObject_StringResolution>();
			ScreenResolution->SetDataID(FName("ScreenResolution"));
			ScreenResolution->SetDataDisplayName(FText::FromString(TEXT("Screen Resolution")));
			ScreenResolution->SetDescriptionRichText(FText::FromString(TEXT("Adjust the screen resolution")));
			ScreenResolution->InitResolutionValues();
			ScreenResolution->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetScreenResolution));
			ScreenResolution->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetScreenResolution));
			ScreenResolution->SetShouldApplySettingsImmediately(true);

			DisplayCategoryCollection->AddChildListData(ScreenResolution);
		}

		VideoTabCollection->AddChildListData(DisplayCategoryCollection);
	}

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
