// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "OptionDataRegistry.generated.h"

/**
 * 
 */
UCLASS()
class GAMEUI_API UOptionDataRegistry : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * 
	 * @param InOwningLocalPlayer 
	 */
	void InitOptionDataRegistry(ULocalPlayer* InOwningLocalPlayer);
};