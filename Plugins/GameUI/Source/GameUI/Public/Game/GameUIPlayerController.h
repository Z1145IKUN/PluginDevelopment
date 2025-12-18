// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameUIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEUI_API AGameUIPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// ~ begin APlayerController Interface
	virtual void OnPossess(APawn* InPawn) override;
	// ~ End APlayerController interface

private:
	UPROPERTY(EditAnywhere, Category="GameUI|Camera",meta=(AllowPrivateAccess="true"))
	FName CameraTag;
};
