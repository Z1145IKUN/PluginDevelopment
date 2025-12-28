// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameUIPlayerController.h"

#include "Camera/CameraActor.h"
#include "DeveloperSettings/GameUIGameUserSettings.h"
#include "Kismet/GameplayStatics.h"

void AGameUIPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClassWithTag(
		this,
		ACameraActor::StaticClass(),
		CameraTag,
		FoundCameras);

	if (!FoundCameras.IsEmpty())
	{
		SetViewTarget(FoundCameras[0]);
	}

	UGameUIGameUserSettings* GameUserSettings = UGameUIGameUserSettings::Get();

	if (GameUserSettings->GetLastCPUBenchmarkResult() == -1.f || GameUserSettings->GetLastGPUBenchmarkResult() == -1.f)
	{
		GameUserSettings->RunHardwareBenchmark();
		GameUserSettings->ApplyHardwareBenchmarkResults();
	}
}
