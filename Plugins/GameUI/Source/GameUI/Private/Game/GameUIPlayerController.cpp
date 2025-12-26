// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameUIPlayerController.h"

#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

void AGameUIPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClassWithTag(this, ACameraActor::StaticClass(), CameraTag, FoundCameras);

	if (!FoundCameras.IsEmpty())
	{
		SetViewTarget(FoundCameras[0]);
	}
}
