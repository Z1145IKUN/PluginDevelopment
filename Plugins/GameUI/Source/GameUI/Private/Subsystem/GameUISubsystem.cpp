// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/GameUISubsystem.h"

UGameUISubsystem* UGameUISubsystem::Get(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);

		return UGameInstance::GetSubsystem<UGameUISubsystem>(World->GetGameInstance());
	}
	return nullptr;
}

bool UGameUISubsystem::ShouldCreateSubsystem(UObject* Outer) const
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

void UGameUISubsystem::RegisterPrimaryLayout(UWidget_PrimaryLayout* InPrimaryLayout)
{
	check(InPrimaryLayout);
	CreatedPrimaryLayout = InPrimaryLayout;
}
