// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/GameUILoadingScreenSubsystem.h"

#include "PreLoadScreenManager.h"
#include "Blueprint/UserWidget.h"
#include "DeveloperSettings/GameUILoadScreenSetting.h"
#include "Interface/GameUILoadingScreenInterface.h"

bool UGameUILoadingScreenSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		TArray<UClass*> FoundClasses;
		// 获取当前类的所有派生类
		GetDerivedClasses(GetClass(), FoundClasses);

		return FoundClasses.IsEmpty();
	}

	return false;
}

void UGameUILoadingScreenSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	FCoreUObjectDelegates::PreLoadMapWithContext.AddUObject(this, &ThisClass::OnMapPreLoaded);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &ThisClass::OnMapPostLoaded);
}

void UGameUILoadingScreenSubsystem::Deinitialize()
{
	FCoreUObjectDelegates::PreLoadMapWithContext.RemoveAll(this);
	FCoreUObjectDelegates::PostLoadMapWithWorld.RemoveAll(this);
}

UWorld* UGameUILoadingScreenSubsystem::GetTickableGameObjectWorld() const
{
	if (UGameInstance* OwningGameInstance = GetGameInstance())
	{
		return OwningGameInstance->GetWorld();
	}
	return nullptr;
}

void UGameUILoadingScreenSubsystem::Tick(float DeltaTime)
{
	TryUpdateLoadingScreen();
}

ETickableTickType UGameUILoadingScreenSubsystem::GetTickableTickType() const
{
	if (IsTemplate())
	{
		return ETickableTickType::Never;
	}
	return ETickableTickType::Conditional;
}

bool UGameUILoadingScreenSubsystem::IsTickable() const
{
	return GetGameInstance() && GetGameInstance()->GetGameViewportClient();
}

TStatId UGameUILoadingScreenSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UGameUILoadingScreenSubsystem, STATGROUP_Tickables);
}

void UGameUILoadingScreenSubsystem::OnMapPreLoaded(const FWorldContext& WorldContext, const FString& MapName)
{
	if (WorldContext.OwningGameInstance != GetGameInstance())
	{
		return;
	}

	SetTickableTickType(ETickableTickType::Conditional);

	bIsCurrentlyLoadingMap = true;

	TryUpdateLoadingScreen();
}

void UGameUILoadingScreenSubsystem::OnMapPostLoaded(UWorld* LoadedWorld)
{
	if (LoadedWorld && LoadedWorld->GetGameInstance() == GetGameInstance())
	{
		bIsCurrentlyLoadingMap = false;
	}
}

void UGameUILoadingScreenSubsystem::TryUpdateLoadingScreen()
{
	//check id there is any start up loading screen that's currently active
	if (IsPreloadScreenActive())
	{
		return;
	}

	//check we should show the loading screen 
	if (ShouldShowLoadingScreen())
	{
		//try display the loading screen there
		TryDisplayLoadingScreenIfNone();

		OnLoadingScreenUpdate.Broadcast(CurrentLoadingReason);
	}
	else
	{
		//try to remove the current active loading screen
		TryRemoveLoadingScreen();
		HoldLoadingScreenStartUpTime = -1.f;

		//Notify the loading is complete
		NotifyLoadingScreenVisibilityChanged(false);

		//Disable the ticking
		SetTickableTickType(ETickableTickType::Never);
	}
}

bool UGameUILoadingScreenSubsystem::IsPreloadScreenActive() const
{
	if (FPreLoadScreenManager* PreLoadScreenManager = FPreLoadScreenManager::Get())
	{
		return PreLoadScreenManager->HasValidActivePreLoadScreen();
	}
	return false;
}

bool UGameUILoadingScreenSubsystem::ShouldShowLoadingScreen()
{
	const UGameUILoadScreenSetting* LoadingScreenSetting = GetDefault<UGameUILoadScreenSetting>();
	if (GIsEditor && !LoadingScreenSetting->bShouldLoadScreenInEditor)
	{
		return false;
	}

	//check if the object is in the world need a loading screen
	if (CheckTheNeedToShowLoadingScreen())
	{
		GetGameInstance()->GetGameViewportClient()->bDisableWorldRendering = true;
		return true;
	}

	CurrentLoadingReason = TEXT("Wait for texture streaming");

	//there is no need to show the loading screen,allow the world to be rendered to our viewport here
	GetGameInstance()->GetGameViewportClient()->bDisableWorldRendering = false;

	const float CurrentTime = FPlatformTime::Seconds();

	if (HoldLoadingScreenStartUpTime < 0.f)
	{
		HoldLoadingScreenStartUpTime = CurrentTime;
	}

	const float ElapsedTime = CurrentTime - HoldLoadingScreenStartUpTime;

	if (ElapsedTime < LoadingScreenSetting->HoldLoadScreenExtraSeconds)
	{
		return true;
	}
	return false;
}

bool UGameUILoadingScreenSubsystem::CheckTheNeedToShowLoadingScreen()
{
	if (bIsCurrentlyLoadingMap)
	{
		CurrentLoadingReason = TEXT("Loading level");
		return true;
	}

	UWorld* World = GetGameInstance()->GetWorld();
	if (!World)
	{
		CurrentLoadingReason = TEXT("Initializing world");
		return true;
	}

	if (!World->HasBegunPlay())
	{
		CurrentLoadingReason = TEXT("World has not begun play yet");
		return true;
	}

	if (!World->GetFirstPlayerController())
	{
		CurrentLoadingReason = TEXT("Player controller is not valid yet");
		return true;
	}

	//check if the game status,or player character,actor component are ready


	return false;
}

void UGameUILoadingScreenSubsystem::TryDisplayLoadingScreenIfNone()
{
	if (CachedCreatedLoadingScreenWidget.IsValid())
	{
		return;
	}

	//if there is already active loading screen ,return early if yes 
	const UGameUILoadScreenSetting* LoadingScreenSetting = GetDefault<UGameUILoadScreenSetting>();

	TSubclassOf<UUserWidget> LoadedWidgetClass = LoadingScreenSetting->GetLoadScreenWidgetClassChecked();

	UUserWidget* CreatedWidget = UUserWidget::CreateWidgetInstance(*GetGameInstance(), LoadedWidgetClass, NAME_None);

	check(CreatedWidget);
	CachedCreatedLoadingScreenWidget = CreatedWidget->TakeWidget();

	GetGameInstance()->GetGameViewportClient()->AddViewportWidgetContent(
		CachedCreatedLoadingScreenWidget.ToSharedRef(),
		1000);

	NotifyLoadingScreenVisibilityChanged(true);
}

void UGameUILoadingScreenSubsystem::TryRemoveLoadingScreen()
{
	if (!CachedCreatedLoadingScreenWidget.IsValid())
	{
		return;
	}
	GetGameInstance()->GetGameViewportClient()->RemoveViewportWidgetContent(
		CachedCreatedLoadingScreenWidget.ToSharedRef());

	CachedCreatedLoadingScreenWidget.Reset();
}

void UGameUILoadingScreenSubsystem::NotifyLoadingScreenVisibilityChanged(bool bIsVisible)
{
	for (ULocalPlayer* ExistingLocalPlayer : GetGameInstance()->GetLocalPlayers())
	{
		if (!ExistingLocalPlayer)
		{
			continue;
		}
		if (APlayerController* PlayerController = ExistingLocalPlayer->GetPlayerController(
			GetGameInstance()->GetWorld()))
		{
			//Query id the player controller implement the interface 
			//call the function through interface to notify the loading screen if yes
			if (PlayerController->Implements<UGameUILoadingScreenInterface>())
			{
				if (bIsVisible)
				{
					IGameUILoadingScreenInterface::Execute_OnLoadingScreenActivated(PlayerController);
				}
				else
				{
					IGameUILoadingScreenInterface::Execute_OnLoadingScreenDeactivated(PlayerController);
				}
			}

			if (APawn* OwningPawn = PlayerController->GetPawn())
			{
				if (OwningPawn->Implements<UGameUILoadingScreenInterface>())
				{
					if (bIsVisible)
					{
						IGameUILoadingScreenInterface::Execute_OnLoadingScreenActivated(OwningPawn);
					}
					else
					{
						IGameUILoadingScreenInterface::Execute_OnLoadingScreenDeactivated(OwningPawn);
					}
				}
			}
		}

		//the code for notify other object in the world goes here
	}
}
