// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/DataObject/ListDataObject_StringResolution.h"

#include "DeveloperSettings/GameUIGameUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"

void UListDataObject_StringResolution::InitResolutionValues()
{
	TArray<FIntPoint> AvailableResolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(AvailableResolutions);

	AvailableResolutions.Sort(
		[](const FIntPoint& A, const FIntPoint& B)-> bool
		{
			return A.SizeSquared() < B.SizeSquared();
		}
	);

	for (const FIntPoint& Resolution : AvailableResolutions)
	{
		AddDynamicOptions(ResolutionValueToString(Resolution), ResolutionValueToText(Resolution));
	}

	MaxAllowResolution = ResolutionValueToString(AvailableResolutions.Last());

	SetDefaultValueFromString(MaxAllowResolution);
}

void UListDataObject_StringResolution::OnDataListObjectInitialized()
{
	Super::OnDataListObjectInitialized();

	if (!SetDisplayTextFromCurrentStringValue(CurrentStringValue))
	{
		CurrentDisplayText = ResolutionValueToText(UGameUIGameUserSettings::Get()->GetScreenResolution());
	}
}

FString UListDataObject_StringResolution::ResolutionValueToString(const FIntPoint& InResolutionValue) const
{
	return FString::Printf(TEXT("(X=%i,Y=%i)"), InResolutionValue.X, InResolutionValue.Y);
}

FText UListDataObject_StringResolution::ResolutionValueToText(const FIntPoint& InResolutionValue) const
{
	const FString DisplayString = FString::Printf(TEXT("%i x %i"), InResolutionValue.X, InResolutionValue.Y);
	return FText::FromString(DisplayString);
}
