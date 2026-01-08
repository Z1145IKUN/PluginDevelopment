// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameUILoadingScreenSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class GAMEUI_API UGameUILoadingScreenSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadingScreenUpdateDelegate, const FString&, CurrentLoadingReason);

	UPROPERTY(BlueprintAssignable)
	FOnLoadingScreenUpdateDelegate OnLoadingScreenUpdate;

	//~ Begin USubsystem interface
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	//~ End USubsystem interface

	//~ Begin FTickableGameObject interface
	virtual UWorld* GetTickableGameObjectWorld() const override;
	virtual void Tick(float DeltaTime) override;
	virtual ETickableTickType GetTickableTickType() const override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	//~ End FTickableGameObject interface

private:
	void OnMapPreLoaded(const FWorldContext& WorldContext, const FString& MapName);
	void OnMapPostLoaded(UWorld* LoadedWorld);

	void TryUpdateLoadingScreen();
	bool IsPreloadScreenActive() const;
	bool ShouldShowLoadingScreen();
	bool CheckTheNeedToShowLoadingScreen();
	void TryDisplayLoadingScreenIfNone();
	void TryRemoveLoadingScreen();
	void NotifyLoadingScreenVisibilityChanged(bool bIsVisible);

	bool bIsCurrentlyLoadingMap = false;
	float HoldLoadingScreenStartUpTime = -1.f;
	FString CurrentLoadingReason;
	TSharedPtr<SWidget> CachedCreatedLoadingScreenWidget;
};
