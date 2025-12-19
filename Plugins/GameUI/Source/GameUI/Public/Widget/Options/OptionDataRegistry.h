// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "OptionDataRegistry.generated.h"

class UListDataObject_Collection;
/**
 * 
 */
UCLASS()
class GAMEUI_API UOptionDataRegistry : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * Init all Option screen tab 
	 * Call immediately after the option Screen is created.
	 * @param InOwningLocalPlayer 
	 */
	void InitOptionDataRegistry(ULocalPlayer* InOwningLocalPlayer);

	TArray<UListDataObject_Collection*> GetRegisteredOptionTabCollections() const;

private:
	void InitGamePlayCollectionTab();
	void InitAudioCollectionTab();
	void InitVideoCollectionTab();
	void InitControlCollectionTab();

	UPROPERTY(Transient)
	TArray<UListDataObject_Collection*> RegisteredOptionsTabCollections;
};
