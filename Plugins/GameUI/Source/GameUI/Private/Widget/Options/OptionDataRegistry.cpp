// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/OptionDataRegistry.h"

#include "EnhancedInputSubsystems.h"
#include "DeveloperSettings/GameUIGameUserSettings.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "Widget/Options/OptionsDataInteractionHelper.h"
#include "Widget/Options/DataObject/ListDataObject_String.h"
#include "Widget/Options/DataObject/ListDataObject_Collection.h"
#include "Widget/Options/DataObject/ListDataObject_KeyRemap.h"
#include "Widget/Options/DataObject/ListDataObject_Scalar.h"
#include "Widget/Options/DataObject/ListDataObject_StringResolution.h"

#define MAKE_DATA_OPTION_CONTROL(GetterOrSetterFuncName) \
	MakeShared<FOptionsDataInteractionHelper> \
	(GET_FUNCTION_NAME_STRING_CHECKED(UGameUIGameUserSettings, GetterOrSetterFuncName))

#define LOCTEXT_NAMESPACE "Options"

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
	GameplayTabCollection->SetDataDisplayName(LOCTEXT("GameplayTab", "Gameplay"));


	//Common Category
	{
		UListDataObject_Collection* CommonCategoryCollection = NewObject<UListDataObject_Collection>();
		CommonCategoryCollection->SetDataID(FName("CommonCategoryCollection"));
		CommonCategoryCollection->SetDataDisplayName(LOCTEXT("CommonCategoryCollection", "Common"));

		//GameDifficult
		{
			UListDataObject_String* GameDifficulty = NewObject<UListDataObject_String>();
			GameDifficulty->SetDataID(FName("GameDifficult"));
			GameDifficulty->SetDataDisplayName(LOCTEXT("Difficulty", "Difficulty"));
			GameDifficulty->AddDynamicOptions(TEXT("Easy"),LOCTEXT("GameDifficult_Easy", "Easy"));
			GameDifficulty->AddDynamicOptions(TEXT("Normal"), LOCTEXT("GameDifficult_Normal", "Normal"));
			GameDifficulty->AddDynamicOptions(TEXT("Hard"), LOCTEXT("GameDifficulty_Hard", "Hard"));
			GameDifficulty->AddDynamicOptions(TEXT("Nightmare"), LOCTEXT("GameDifficult_Nightmare", "Nightmare"));
			GameDifficulty->SetDefaultValueFromString(TEXT("Normal"));
			GameDifficulty->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetCurrentDifficulty));
			GameDifficulty->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetCurrentDifficulty));
			GameDifficulty->SetShouldApplySettingsImmediately(true);

			CommonCategoryCollection->AddChildListData(GameDifficulty);
		}

		GameplayTabCollection->AddChildListData(CommonCategoryCollection);
	}

	RegisteredOptionsTabCollections.Add(GameplayTabCollection);
}

void UOptionDataRegistry::InitAudioCollectionTab()
{
	UListDataObject_Collection* AudioTabCollection = NewObject<UListDataObject_Collection>();

	AudioTabCollection->SetDataID(FName("AudioTabCollection"));
	AudioTabCollection->SetDataDisplayName(LOCTEXT("AudioTab", "Audio"));

	//Volume Category
	{
		UListDataObject_Collection* VolumeCategoryCollection = NewObject<UListDataObject_Collection>();
		VolumeCategoryCollection->SetDataID(FName("VolumeCategoryCollection"));
		VolumeCategoryCollection->SetDataDisplayName(LOCTEXT("VolumeCategoryCollection", "Volume"));

		//overall volume
		{
			UListDataObject_Scalar* OverallVolume = NewObject<UListDataObject_Scalar>();
			OverallVolume->SetDataID(FName("OverallVolume"));
			OverallVolume->SetDataDisplayName(LOCTEXT("OverallVolume", "Overall Volume"));
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
			MusicVolume->SetDataDisplayName(LOCTEXT("MusicVolume", "Music Volume"));
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
			SoundFXVolume->SetDataDisplayName(LOCTEXT("SoundFXVolume", "Sound Effects Volume"));
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
		SoundCategory->SetDataDisplayName(LOCTEXT("SoundCategory", "Sound"));

		//Allow Background Audio
		{
			UListDataObject_StringBool* AllowBackgroundAudio = NewObject<UListDataObject_StringBool>();
			AllowBackgroundAudio->SetDataID(FName("AllowBackgroundAudio"));
			AllowBackgroundAudio->SetDataDisplayName(LOCTEXT("AllowBackgroundAudio", "Allow Background Audio"));
			AllowBackgroundAudio->OverrideTrueDisplayText(LOCTEXT("Enable", "Enable"));
			AllowBackgroundAudio->OverrideFalseDisplayText(LOCTEXT("Disable", "Disable"));
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
			UseHDRAudio->SetDataDisplayName(LOCTEXT("UseHDRAudio", "Use HDR Audio"));
			UseHDRAudio->OverrideTrueDisplayText(LOCTEXT("Enable", "Enable"));
			UseHDRAudio->OverrideFalseDisplayText(LOCTEXT("Disable", "Disable"));
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
	VideoTabCollection->SetDataDisplayName(LOCTEXT("VideoTab", "Video"));

	UListDataObject_StringEnum* WindowMode = NewObject<UListDataObject_StringEnum>();

	// Display Category Collection 
	{
		UListDataObject_Collection* DisplayCategoryCollection = NewObject<UListDataObject_Collection>();
		DisplayCategoryCollection->SetDataID(FName("DisplayCategoryCollection"));
		DisplayCategoryCollection->SetDataDisplayName(LOCTEXT("DisplayCategoryCollection", "Display"));

		UListDataObject_StringResolution* ScreenResolution = NewObject<UListDataObject_StringResolution>();

		//Window mode
		{
			WindowMode->SetDataID(FName("WindowMode"));
			WindowMode->SetDataDisplayName(LOCTEXT("WindowMode", "Window Mode"));
			WindowMode->AddEnumOption(EWindowMode::Type::Fullscreen, LOCTEXT("Fullscreen", "Fullscreen"));
			WindowMode->AddEnumOption(EWindowMode::Type::WindowedFullscreen,
			                          LOCTEXT("WindowedFullscreen", "Borderless Window"));
			WindowMode->AddEnumOption(EWindowMode::Type::Windowed, LOCTEXT("Windowed", "Windowed"));
			WindowMode->SetDefaultValueFromEnumOption(EWindowMode::Type::WindowedFullscreen);
			WindowMode->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetWindowMode));
			WindowMode->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetWindowMode));
			WindowMode->SetShouldApplySettingsImmediately(true);

			DisplayCategoryCollection->AddChildListData(WindowMode);
		}

		//Screen Resolution
		{
			ScreenResolution->SetDataID(FName("ScreenResolution"));
			ScreenResolution->SetDataDisplayName(LOCTEXT("ScreenResolution", "Screen Resolution"));
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
			//TODO: use String Table
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
		GraphicsCategoryCollection->SetDataDisplayName(LOCTEXT("GraphicsCategoryCollection", "Graphics"));

		UListDataObject_StringInteger* OverallQuality = NewObject<UListDataObject_StringInteger>();

		//Display Gamma
		{
			UListDataObject_Scalar* DisplayGamma = NewObject<UListDataObject_Scalar>();
			DisplayGamma->SetDataID(FName("DisplayGamma"));
			DisplayGamma->SetDataDisplayName(LOCTEXT("DisplayGamma", "Brightness"));
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
			OverallQuality->SetDataDisplayName(LOCTEXT("OverallQuality", "Overall Quality"));
			OverallQuality->AddIntegerOption(0, LOCTEXT("Low", "Low"));
			OverallQuality->AddIntegerOption(1, LOCTEXT("Medium", "Medium"));
			OverallQuality->AddIntegerOption(2, LOCTEXT("High", "High"));
			OverallQuality->AddIntegerOption(3, LOCTEXT("Epic", "Epic"));
			OverallQuality->AddIntegerOption(4, LOCTEXT("Cinematic", "Cinematic"));
			OverallQuality->SetDataDynamicGetter(MAKE_DATA_OPTION_CONTROL(GetOverallScalabilityLevel));
			OverallQuality->SetDataDynamicSetter(MAKE_DATA_OPTION_CONTROL(SetOverallScalabilityLevel));
			OverallQuality->SetShouldApplySettingsImmediately(true);

			GraphicsCategoryCollection->AddChildListData(OverallQuality);
		}

		//Resolution Scale 动态分辨率缩放
		{
			UListDataObject_Scalar* ResolutionScale = NewObject<UListDataObject_Scalar>();
			ResolutionScale->SetDataID(FName("ResolutionScale"));
			ResolutionScale->SetDataDisplayName(LOCTEXT("ResolutionScale", "3D Resolution"));
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
			GlobalIlluminationQuality->SetDataDisplayName(
				LOCTEXT("GlobalIlluminationQuality", "Global Illumination Quality"));
			GlobalIlluminationQuality->AddIntegerOption(0, LOCTEXT("Low", "Low"));
			GlobalIlluminationQuality->AddIntegerOption(1, LOCTEXT("Medium", "Medium"));
			GlobalIlluminationQuality->AddIntegerOption(2, LOCTEXT("High", "High"));
			GlobalIlluminationQuality->AddIntegerOption(3, LOCTEXT("Epic", "Epic"));
			GlobalIlluminationQuality->AddIntegerOption(4, LOCTEXT("Cinematic", "Cinematic"));
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
			ShadowQuality->SetDataDisplayName(LOCTEXT("ShadowQuality", "Shadow Quality"));
			ShadowQuality->AddIntegerOption(0, LOCTEXT("Low", "Low"));
			ShadowQuality->AddIntegerOption(1, LOCTEXT("Medium", "Medium"));
			ShadowQuality->AddIntegerOption(2, LOCTEXT("High", "High"));
			ShadowQuality->AddIntegerOption(3, LOCTEXT("Epic", "Epic"));
			ShadowQuality->AddIntegerOption(4, LOCTEXT("Cinematic", "Cinematic"));
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
			AntiAliasingQuality->SetDataDisplayName(LOCTEXT("AntiAliasingQuality", "Anti Aliasing Quality"));
			AntiAliasingQuality->AddIntegerOption(0, LOCTEXT("Low", "Low"));
			AntiAliasingQuality->AddIntegerOption(1, LOCTEXT("Medium", "Medium"));
			AntiAliasingQuality->AddIntegerOption(2, LOCTEXT("High", "High"));
			AntiAliasingQuality->AddIntegerOption(3, LOCTEXT("Epic", "Epic"));
			AntiAliasingQuality->AddIntegerOption(4, LOCTEXT("Cinematic", "Cinematic"));
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
			ViewDistanceQuality->SetDataDisplayName(LOCTEXT("ViewDistanceQuality", "View Distance Quality"));
			ViewDistanceQuality->AddIntegerOption(0, LOCTEXT("Near", "Near"));
			ViewDistanceQuality->AddIntegerOption(1, LOCTEXT("Medium", "Medium"));
			ViewDistanceQuality->AddIntegerOption(2, LOCTEXT("Far", "Far"));
			ViewDistanceQuality->AddIntegerOption(3, LOCTEXT("VeryFar", "Very Far"));
			ViewDistanceQuality->AddIntegerOption(4, LOCTEXT("Cinematic", "Cinematic"));
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
			TextureQuality->SetDataDisplayName(LOCTEXT("TextureQuality", "Texture Quality"));
			TextureQuality->AddIntegerOption(0, LOCTEXT("Low", "Low"));
			TextureQuality->AddIntegerOption(1, LOCTEXT("Medium", "Medium"));
			TextureQuality->AddIntegerOption(2, LOCTEXT("High", "High"));
			TextureQuality->AddIntegerOption(3, LOCTEXT("Epic", "Epic"));
			TextureQuality->AddIntegerOption(4, LOCTEXT("Cinematic", "Cinematic"));
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
			VisualEffectQuality->SetDataDisplayName(LOCTEXT("VisualEffectQuality", "Visual Effect Quality"));
			VisualEffectQuality->AddIntegerOption(0, LOCTEXT("Low", "Low"));
			VisualEffectQuality->AddIntegerOption(1, LOCTEXT("Medium", "Medium"));
			VisualEffectQuality->AddIntegerOption(2, LOCTEXT("High", "High"));
			VisualEffectQuality->AddIntegerOption(3, LOCTEXT("Epic", "Epic"));
			VisualEffectQuality->AddIntegerOption(4, LOCTEXT("Cinematic", "Cinematic"));
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
			ReflectionQuality->SetDataDisplayName(LOCTEXT("ReflectionQuality", "Reflection Quality"));
			ReflectionQuality->AddIntegerOption(0, LOCTEXT("Low", "Low"));
			ReflectionQuality->AddIntegerOption(1, LOCTEXT("Medium", "Medium"));
			ReflectionQuality->AddIntegerOption(2, LOCTEXT("High", "High"));
			ReflectionQuality->AddIntegerOption(3, LOCTEXT("Epic", "Epic"));
			ReflectionQuality->AddIntegerOption(4, LOCTEXT("Cinematic", "Cinematic"));
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
			PostProcessingQuality->SetDataDisplayName(LOCTEXT("PostProcessingQuality", "Post Processing Quality"));
			PostProcessingQuality->AddIntegerOption(0, LOCTEXT("Low", "Low"));
			PostProcessingQuality->AddIntegerOption(1, LOCTEXT("Medium", "Medium"));
			PostProcessingQuality->AddIntegerOption(2, LOCTEXT("High", "High"));
			PostProcessingQuality->AddIntegerOption(3, LOCTEXT("Epic", "Epic"));
			PostProcessingQuality->AddIntegerOption(4, LOCTEXT("Cinematic", "Cinematic"));
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
		AdvanceGraphicsCategoryCollection->SetDataDisplayName(
			LOCTEXT("AdvanceGraphicsCategoryCollection", "Advance Graphics"));

		//vertical Sync	垂直同步
		{
			UListDataObject_StringBool* VerticalSync = NewObject<UListDataObject_StringBool>();
			VerticalSync->SetDataID(FName("VerticalSync"));
			VerticalSync->SetDataDisplayName(LOCTEXT("VerticalSync", "V-Sync"));
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
			//TODO: use String Table
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
			FrameRateLimit->SetDataDisplayName(LOCTEXT("FrameRateLimit", "Frame Rate Limit"));
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

void UOptionDataRegistry::InitControlCollectionTab(const ULocalPlayer* InOwningLocalPlayer)
{
	UListDataObject_Collection* ControlTabCollection = NewObject<UListDataObject_Collection>();

	ControlTabCollection->SetDataID(FName("ControlTabCollection"));
	ControlTabCollection->SetDataDisplayName(LOCTEXT("ControlTab", "Control"));

	UEnhancedInputLocalPlayerSubsystem* EISubsystem = InOwningLocalPlayer->
		GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(EISubsystem);
	UEnhancedInputUserSettings* EIUSerSettings = EISubsystem->GetUserSettings();
	check(EIUSerSettings);

	//Keyboard Mouse Category
	{
		UListDataObject_Collection* KeyboardMouseCollectionCategory = NewObject<UListDataObject_Collection>();
		KeyboardMouseCollectionCategory->SetDataID(FName("KeyboardMouseCollectionCategory"));
		KeyboardMouseCollectionCategory->SetDataDisplayName(LOCTEXT("MouseAndKeyboard", "Mouse & Keyboard"));

		//Keyboard Mouse Inputs
		{
			FPlayerMappableKeyQueryOptions KeyboardMouseOnly;
			KeyboardMouseOnly.KeyToMatch = EKeys::S;
			KeyboardMouseOnly.bMatchBasicKeyTypes = true;

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
							UListDataObject_KeyRemap* KeyRemapDataObject = NewObject<UListDataObject_KeyRemap>();
							KeyRemapDataObject->SetDataID(KeyMapping.GetMappingName());
							KeyRemapDataObject->SetDataDisplayName(KeyMapping.GetDisplayName());
							KeyRemapDataObject->InitKeyRemapData(
								EIUSerSettings,
								MappableKeyProfile,
								ECommonInputType::MouseAndKeyboard,
								KeyMapping);

							KeyboardMouseCollectionCategory->AddChildListData(KeyRemapDataObject);
						}
					}
				}
			}
		}

		ControlTabCollection->AddChildListData(KeyboardMouseCollectionCategory);
	}

	//Gamepad Category
	{
		UListDataObject_Collection* GamepadCollectionCategory = NewObject<UListDataObject_Collection>();
		GamepadCollectionCategory->SetDataID(FName("GamepadCollectionCategory"));
		GamepadCollectionCategory->SetDataDisplayName(LOCTEXT("Gamepad", "Gamepad"));

		//Gamepad inputs
		{
			{
				FPlayerMappableKeyQueryOptions GamepadOnly;
				GamepadOnly.KeyToMatch = EKeys::Gamepad_FaceButton_Bottom;
				GamepadOnly.bMatchBasicKeyTypes = true;

				//Traverse all available key configuration files
				//配置方案
				for (const TPair<FString, TObjectPtr<UEnhancedPlayerMappableKeyProfile>>& ProfilePair :
				     EIUSerSettings->GetAllAvailableKeyProfiles())
				{
					UEnhancedPlayerMappableKeyProfile* MappableKeyProfile = ProfilePair.Value;

					check(MappableKeyProfile);

					//映射行
					for (const TPair<FName, FKeyMappingRow>& MappingRowPair : MappableKeyProfile->
					     GetPlayerMappingRows())
					{
						//具体映射
						for (const FPlayerKeyMapping& KeyMapping : MappingRowPair.Value.Mappings)
						{
							if (MappableKeyProfile->DoesMappingPassQueryOptions(KeyMapping, GamepadOnly))
							{
								UListDataObject_KeyRemap* KeyRemapDataObject = NewObject<UListDataObject_KeyRemap>();
								KeyRemapDataObject->SetDataID(KeyMapping.GetMappingName());
								KeyRemapDataObject->SetDataDisplayName(KeyMapping.GetDisplayName());
								KeyRemapDataObject->InitKeyRemapData(
									EIUSerSettings,
									MappableKeyProfile,
									ECommonInputType::Gamepad,
									KeyMapping);

								GamepadCollectionCategory->AddChildListData(KeyRemapDataObject);
							}
						}
					}
				}
			}
		}

		ControlTabCollection->AddChildListData(GamepadCollectionCategory);
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
#undef LOCTEXT_NAMESPACE
