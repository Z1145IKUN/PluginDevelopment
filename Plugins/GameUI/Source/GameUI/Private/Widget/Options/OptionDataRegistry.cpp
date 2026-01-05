// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/OptionDataRegistry.h"

#include "EnhancedInputSubsystems.h"
#include "DeveloperSettings/GameUIGameUserSettings.h"
#include "UserSettings/EnhancedInputUserSettings.h"
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
	InitControlCollectionTab(InOwningLocalPlayer);
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

	UListDataObject_StringEnum* WindowMode = NewObject<UListDataObject_StringEnum>();

	// Display Category Collection 
	{
		UListDataObject_Collection* DisplayCategoryCollection = NewObject<UListDataObject_Collection>();
		DisplayCategoryCollection->SetDataID(FName("DisplayCategoryCollection"));
		DisplayCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Display")));

		UListDataObject_StringResolution* ScreenResolution = NewObject<UListDataObject_StringResolution>();

		//Window mode
		{
			WindowMode->SetDataID(FName("WindowMode"));
			WindowMode->SetDataDisplayName(FText::FromString(TEXT("Window Mode")));
			WindowMode->SetDescriptionRichText(FText::FromString(TEXT("Adjust the window mode")));
			WindowMode->AddEnumOption(EWindowMode::Type::Fullscreen, FText::FromString(TEXT("Fullscreen")));
			WindowMode->AddEnumOption(EWindowMode::Type::WindowedFullscreen,
			                          FText::FromString(TEXT("Borderless Window")));
			WindowMode->AddEnumOption(EWindowMode::Type::Windowed, FText::FromString(TEXT("Windowed")));
			WindowMode->SetDefaultValueFromEnumOption(EWindowMode::Type::WindowedFullscreen);
			WindowMode->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetWindowMode));
			WindowMode->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetWindowMode));
			WindowMode->SetShouldApplySettingsImmediately(true);

			DisplayCategoryCollection->AddChildListData(WindowMode);
		}

		//Screen Resolution
		{
			ScreenResolution->SetDataID(FName("ScreenResolution"));
			ScreenResolution->SetDataDisplayName(FText::FromString(TEXT("Screen Resolution")));
			ScreenResolution->SetDescriptionRichText(FText::FromString(TEXT("Adjust the screen resolution")));
			ScreenResolution->InitResolutionValues();
			ScreenResolution->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetScreenResolution));
			ScreenResolution->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetScreenResolution));
			ScreenResolution->SetShouldApplySettingsImmediately(true);

			FOptionsDataEditConditionDescriptor WindowModeEditCondition;
			WindowModeEditCondition.SetEditConditionFunc(
				[WindowMode]()-> bool
				{
					const bool bIsBorderlessWindow = WindowMode->GetCurrentValueAsEnum<EWindowMode::Type>() ==
						EWindowMode::Type::WindowedFullscreen;

					return !bIsBorderlessWindow;
				}
			);
			WindowModeEditCondition.SetDisabledRichReason(TEXT(
				"\n\n<Disabled>Screen Resolution is not adjust when the window mode is set to borderless window</>"));
			WindowModeEditCondition.SetDisabledForcedStringValue(ScreenResolution->GetMaxAllowResolution());
			ScreenResolution->AddEditCondition(WindowModeEditCondition);
			ScreenResolution->AddEditDependencyData(WindowMode);

			DisplayCategoryCollection->AddChildListData(ScreenResolution);
		}

		VideoTabCollection->AddChildListData(DisplayCategoryCollection);
	}

	//Graphics Category Collection
	{
		UListDataObject_Collection* GraphicsCategoryCollection = NewObject<UListDataObject_Collection>();
		GraphicsCategoryCollection->SetDataID(FName("GraphicsCategoryCollection"));
		GraphicsCategoryCollection->SetDataDisplayName(FText::FromString("Graphics"));

		UListDataObject_StringInteger* OverallQuality = NewObject<UListDataObject_StringInteger>();

		//Display Gamma
		{
			UListDataObject_Scalar* DisplayGamma = NewObject<UListDataObject_Scalar>();
			DisplayGamma->SetDataID(FName("DisplayGamma"));
			DisplayGamma->SetDataDisplayName(FText::FromString(TEXT("Brightness")));
			DisplayGamma->SetDescriptionRichText(FText::FromString(TEXT("Adjust the screen brightness")));
			DisplayGamma->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			DisplayGamma->SetOutputValueRange(TRange<float>(1.7f, 2.7f));
			DisplayGamma->SetSliderStepSize(0.01f);
			DisplayGamma->SetDisplayNumericType(ECommonNumericType::Percentage);
			DisplayGamma->SetNumberFormattingOptions(UListDataObject_Scalar::NoDecimal());
			DisplayGamma->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetCurrentDisplayGamma));
			DisplayGamma->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetCurrentDisplayGamma));
			DisplayGamma->SetDefaultValueFromString(LexToString(2.2f));

			GraphicsCategoryCollection->AddChildListData(DisplayGamma);
		}

		//Overall Quality
		{
			OverallQuality->SetDataID(FName("OverallQuality"));
			OverallQuality->SetDataDisplayName(FText::FromString(TEXT("Overall Quality")));
			OverallQuality->SetDescriptionRichText(FText::FromString(TEXT("Adjust the overall quality")));
			OverallQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			OverallQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			OverallQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			OverallQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			OverallQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			OverallQuality->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetOverallScalabilityLevel));
			OverallQuality->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetOverallScalabilityLevel));
			OverallQuality->SetShouldApplySettingsImmediately(true);

			GraphicsCategoryCollection->AddChildListData(OverallQuality);
		}

		//Resolution Scale 动态分辨率缩放
		{
			UListDataObject_Scalar* ResolutionScale = NewObject<UListDataObject_Scalar>();
			ResolutionScale->SetDataID(FName("ResolutionScale"));
			ResolutionScale->SetDataDisplayName(FText::FromString(TEXT("3D Resolution")));
			ResolutionScale->SetDescriptionRichText(FText::FromString(TEXT("Adjust the resolution scale")));
			ResolutionScale->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			ResolutionScale->SetOutputValueRange(TRange<float>(0.f, 1.f));
			ResolutionScale->SetSliderStepSize(0.01f);
			ResolutionScale->SetDisplayNumericType(ECommonNumericType::Percentage);
			ResolutionScale->SetNumberFormattingOptions(UListDataObject_Scalar::NoDecimal());
			ResolutionScale->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetResolutionScaleNormalized));
			ResolutionScale->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetResolutionScaleNormalized));
			ResolutionScale->SetShouldApplySettingsImmediately(true);

			ResolutionScale->AddEditDependencyData(OverallQuality);

			GraphicsCategoryCollection->AddChildListData(ResolutionScale);
		}

		//Global Illumination Quality 全局光照质量
		{
			UListDataObject_StringInteger* GlobalIlluminationQuality = NewObject<UListDataObject_StringInteger>();
			GlobalIlluminationQuality->SetDataID(FName("GlobalIlluminationQuality"));
			GlobalIlluminationQuality->SetDataDisplayName(FText::FromString(TEXT("Global Illumination Quality")));
			GlobalIlluminationQuality->SetDescriptionRichText(
				FText::FromString(TEXT("Adjust the global illumination quality")));
			GlobalIlluminationQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			GlobalIlluminationQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			GlobalIlluminationQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			GlobalIlluminationQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			GlobalIlluminationQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			GlobalIlluminationQuality->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetGlobalIlluminationQuality));
			GlobalIlluminationQuality->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetGlobalIlluminationQuality));
			GlobalIlluminationQuality->SetShouldApplySettingsImmediately(true);

			GlobalIlluminationQuality->AddEditDependencyData(OverallQuality);
			OverallQuality->AddEditDependencyData(GlobalIlluminationQuality);

			GraphicsCategoryCollection->AddChildListData(GlobalIlluminationQuality);
		}

		//Shadow Quality
		{
			UListDataObject_StringInteger* ShadowQuality = NewObject<UListDataObject_StringInteger>();
			ShadowQuality->SetDataID(FName("ShadowQuality"));
			ShadowQuality->SetDataDisplayName(FText::FromString(TEXT("Shadow Quality")));
			ShadowQuality->SetDescriptionRichText(
				FText::FromString(TEXT("Adjust the global Shadow quality")));
			ShadowQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			ShadowQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			ShadowQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			ShadowQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			ShadowQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			ShadowQuality->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetShadowQuality));
			ShadowQuality->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetShadowQuality));
			ShadowQuality->SetShouldApplySettingsImmediately(true);

			ShadowQuality->AddEditDependencyData(OverallQuality);
			OverallQuality->AddEditDependencyData(ShadowQuality);

			GraphicsCategoryCollection->AddChildListData(ShadowQuality);
		}

		//AntiAliasing Quality 抗锯齿质量
		{
			UListDataObject_StringInteger* AntiAliasingQuality = NewObject<UListDataObject_StringInteger>();
			AntiAliasingQuality->SetDataID(FName("AntiAliasingQuality"));
			AntiAliasingQuality->SetDataDisplayName(FText::FromString(TEXT("Anti Aliasing")));
			AntiAliasingQuality->SetDescriptionRichText(
				FText::FromString(TEXT("Adjust the global AntiAliasing quality")));
			AntiAliasingQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			AntiAliasingQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			AntiAliasingQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			AntiAliasingQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			AntiAliasingQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			AntiAliasingQuality->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetAntiAliasingQuality));
			AntiAliasingQuality->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetAntiAliasingQuality));
			AntiAliasingQuality->SetShouldApplySettingsImmediately(true);

			AntiAliasingQuality->AddEditDependencyData(OverallQuality);
			OverallQuality->AddEditDependencyData(AntiAliasingQuality);

			GraphicsCategoryCollection->AddChildListData(AntiAliasingQuality);
		}

		//View Distance Quality
		{
			UListDataObject_StringInteger* ViewDistanceQuality = NewObject<UListDataObject_StringInteger>();
			ViewDistanceQuality->SetDataID(FName("ViewDistanceQuality"));
			ViewDistanceQuality->SetDataDisplayName(FText::FromString(TEXT("View Distance")));
			ViewDistanceQuality->SetDescriptionRichText(
				FText::FromString(TEXT("Adjust the global AntiAliasing quality")));
			ViewDistanceQuality->AddIntegerOption(0, FText::FromString(TEXT("Near")));
			ViewDistanceQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			ViewDistanceQuality->AddIntegerOption(2, FText::FromString(TEXT("Far")));
			ViewDistanceQuality->AddIntegerOption(3, FText::FromString(TEXT("Very Far")));
			ViewDistanceQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			ViewDistanceQuality->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetViewDistanceQuality));
			ViewDistanceQuality->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetViewDistanceQuality));
			ViewDistanceQuality->SetShouldApplySettingsImmediately(true);

			ViewDistanceQuality->AddEditDependencyData(OverallQuality);
			OverallQuality->AddEditDependencyData(ViewDistanceQuality);

			GraphicsCategoryCollection->AddChildListData(ViewDistanceQuality);
		}

		//Texture Quality
		{
			UListDataObject_StringInteger* TextureQuality = NewObject<UListDataObject_StringInteger>();
			TextureQuality->SetDataID(FName("TextureQuality"));
			TextureQuality->SetDataDisplayName(FText::FromString(TEXT("Texture Quality")));
			TextureQuality->SetDescriptionRichText(
				FText::FromString(TEXT("Adjust the global AntiAliasing quality")));
			TextureQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			TextureQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			TextureQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			TextureQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			TextureQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			TextureQuality->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetTextureQuality));
			TextureQuality->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetTextureQuality));
			TextureQuality->SetShouldApplySettingsImmediately(true);

			TextureQuality->AddEditDependencyData(OverallQuality);
			OverallQuality->AddEditDependencyData(TextureQuality);

			GraphicsCategoryCollection->AddChildListData(TextureQuality);
		}

		//Visual Effect Quality
		{
			UListDataObject_StringInteger* VisualEffectQuality = NewObject<UListDataObject_StringInteger>();
			VisualEffectQuality->SetDataID(FName("VisualEffectQuality"));
			VisualEffectQuality->SetDataDisplayName(FText::FromString(TEXT("Visual Effect Quality")));
			VisualEffectQuality->SetDescriptionRichText(
				FText::FromString(TEXT("Adjust the global AntiAliasing quality")));
			VisualEffectQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			VisualEffectQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			VisualEffectQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			VisualEffectQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			VisualEffectQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			VisualEffectQuality->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetVisualEffectQuality));
			VisualEffectQuality->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetVisualEffectQuality));
			VisualEffectQuality->SetShouldApplySettingsImmediately(true);

			VisualEffectQuality->AddEditDependencyData(OverallQuality);
			OverallQuality->AddEditDependencyData(VisualEffectQuality);

			GraphicsCategoryCollection->AddChildListData(VisualEffectQuality);
		}

		//Reflection Quality
		{
			UListDataObject_StringInteger* ReflectionQuality = NewObject<UListDataObject_StringInteger>();
			ReflectionQuality->SetDataID(FName("ReflectionQuality"));
			ReflectionQuality->SetDataDisplayName(FText::FromString(TEXT("Reflection Quality")));
			ReflectionQuality->SetDescriptionRichText(
				FText::FromString(TEXT("Adjust the global AntiAliasing quality")));
			ReflectionQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			ReflectionQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			ReflectionQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			ReflectionQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			ReflectionQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			ReflectionQuality->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetReflectionQuality));
			ReflectionQuality->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetReflectionQuality));
			ReflectionQuality->SetShouldApplySettingsImmediately(true);

			ReflectionQuality->AddEditDependencyData(OverallQuality);
			OverallQuality->AddEditDependencyData(ReflectionQuality);

			GraphicsCategoryCollection->AddChildListData(ReflectionQuality);
		}

		//Post Processing Quality
		{
			UListDataObject_StringInteger* PostProcessingQuality = NewObject<UListDataObject_StringInteger>();
			PostProcessingQuality->SetDataID(FName("PostProcessingQuality"));
			PostProcessingQuality->SetDataDisplayName(FText::FromString(TEXT("Post Processing Quality")));
			PostProcessingQuality->SetDescriptionRichText(
				FText::FromString(TEXT("Adjust the global AntiAliasing quality")));
			PostProcessingQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			PostProcessingQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			PostProcessingQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			PostProcessingQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			PostProcessingQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			PostProcessingQuality->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetPostProcessingQuality));
			PostProcessingQuality->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetPostProcessingQuality));
			PostProcessingQuality->SetShouldApplySettingsImmediately(true);

			PostProcessingQuality->AddEditDependencyData(OverallQuality);
			OverallQuality->AddEditDependencyData(PostProcessingQuality);

			GraphicsCategoryCollection->AddChildListData(PostProcessingQuality);
		}

		VideoTabCollection->AddChildListData(GraphicsCategoryCollection);
	}

	//Advance Graphics Category Collection
	{
		UListDataObject_Collection* AdvanceGraphicsCategoryCollection = NewObject<UListDataObject_Collection>();
		AdvanceGraphicsCategoryCollection->SetDataID(FName("AdvanceGraphicsCategoryCollection"));
		AdvanceGraphicsCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Advance Graphics")));

		//vertical Sync	垂直同步
		{
			UListDataObject_StringBool* VerticalSync = NewObject<UListDataObject_StringBool>();
			VerticalSync->SetDataID(FName("VerticalSync"));
			VerticalSync->SetDataDisplayName(FText::FromString(TEXT("V-Sync")));
			VerticalSync->SetDescriptionRichText(FText::FromString(TEXT("Adjust Vertical Sync")));
			VerticalSync->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(IsVSyncEnabled));
			VerticalSync->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetVSyncEnabled));
			VerticalSync->SetFalseAsDefaultString();
			VerticalSync->SetShouldApplySettingsImmediately(true);

			FOptionsDataEditConditionDescriptor FullScreenOnlyCondition;
			FullScreenOnlyCondition.SetEditConditionFunc(
				[WindowMode]()-> bool
				{
					return WindowMode->GetCurrentValueAsEnum<EWindowMode::Type>() == EWindowMode::Type::Fullscreen;
				}
			);
			FullScreenOnlyCondition.SetDisabledRichReason(
				TEXT("\n\n<Disabled>This feature only Works if the window mode is set to full screen</>"));
			FullScreenOnlyCondition.SetDisabledForcedStringValue(TEXT("false"));
			VerticalSync->AddEditCondition(FullScreenOnlyCondition);

			AdvanceGraphicsCategoryCollection->AddChildListData(VerticalSync);
		}

		//Frame Rate Limit
		{
			UListDataObject_String* FrameRateLimit = NewObject<UListDataObject_String>();
			FrameRateLimit->SetDataID(FName("FrameRateLimit"));
			FrameRateLimit->SetDataDisplayName(FText::FromString(TEXT("Frame Rate Limit")));
			FrameRateLimit->SetDescriptionRichText(FText::FromString(TEXT("Adjust Frame Rate Limit")));
			FrameRateLimit->AddDynamicOptions(LexToString(30.f), FText::FromString(TEXT("30 FPS")));
			FrameRateLimit->AddDynamicOptions(LexToString(60.f), FText::FromString(TEXT("60 FPS")));
			FrameRateLimit->AddDynamicOptions(LexToString(90.f), FText::FromString(TEXT("90 FPS")));
			FrameRateLimit->AddDynamicOptions(LexToString(120.f), FText::FromString(TEXT("120 FPS")));
			FrameRateLimit->AddDynamicOptions(LexToString(0.f), FText::FromString(TEXT("No Limit")));
			FrameRateLimit->SetDefaultValueFromString(LexToString(60.f));
			FrameRateLimit->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetFrameRateLimit));
			FrameRateLimit->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetFrameRateLimit));
			FrameRateLimit->SetShouldApplySettingsImmediately(true);

			AdvanceGraphicsCategoryCollection->AddChildListData(FrameRateLimit);
		}

		VideoTabCollection->AddChildListData(AdvanceGraphicsCategoryCollection);
	}

	RegisteredOptionsTabCollections.Add(VideoTabCollection);
}

void UOptionDataRegistry::InitControlCollectionTab(ULocalPlayer* InOwningLocalPlayer)
{
	UListDataObject_Collection* ControlTabCollection = NewObject<UListDataObject_Collection>();

	ControlTabCollection->SetDataID(FName("ControlTabCollection"));
	ControlTabCollection->SetDataDisplayName(FText::FromString("Control"));

	UEnhancedInputLocalPlayerSubsystem* EISubsystem = InOwningLocalPlayer->
		GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(EISubsystem);
	UEnhancedInputUserSettings* EIUSerSettings = EISubsystem->GetUserSettings();
	check(EIUSerSettings);

	//Keyboard Mouse Category
	{
		UListDataObject_Collection* KeyboardMouseCollectionCategory = NewObject<UListDataObject_Collection>();
		KeyboardMouseCollectionCategory->SetDataID(FName("KeyboardMouseCollectionCategory"));
		KeyboardMouseCollectionCategory->SetDataDisplayName(FText::FromString(TEXT("Keyboard & Mouse")));

		//Keyboard Mouse Inputs
		{
			FPlayerMappableKeyQueryOptions KeyboardMouseOnly;
			KeyboardMouseOnly.KeyToMatch = EKeys::S;
			KeyboardMouseOnly.bMatchBasicKeyTypes = true;

			// FPlayerMappableKeyQueryOptions GamepadOnly;
			// GamepadOnly.KeyToMatch = EKeys::Gamepad_FaceButton_Bottom;
			// GamepadOnly.bMatchBasicKeyTypes = true;

			//Traverse all available key configuration files
			for (const TPair<FString, TObjectPtr<UEnhancedPlayerMappableKeyProfile>>& ProfilePair :
			     EIUSerSettings->GetAllAvailableKeyProfiles())
			{
				UEnhancedPlayerMappableKeyProfile* MappableKeyProfile = ProfilePair.Value;

				check(MappableKeyProfile);

				for (const TPair<FName, FKeyMappingRow>& MappingRowPair : MappableKeyProfile->GetPlayerMappingRows())
				{
					for (const FPlayerKeyMapping& KeyMapping : MappingRowPair.Value.Mappings)
					{
						if (MappableKeyProfile->DoesMappingPassQueryOptions(KeyMapping, KeyboardMouseOnly))
						{
						}
					}
				}
			}
		}

		ControlTabCollection->AddChildListData(KeyboardMouseCollectionCategory);
	}

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
