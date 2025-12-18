// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/GameUISubsystem.h"
#include "Widget/Widget_ActivatableBase.h"
#include "Widget/Widget_PrimaryLayout.h"
#include "Engine/AssetManager.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

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

void UGameUISubsystem::PushSoftWidgetToStack(
	const FGameplayTag& InStackTag,
	TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,
	TFunction<void(EAsyncPushWidgetState, UWidget_ActivatableBase*)> AsyncPushStateCallBack)
{
	check(!InSoftWidgetClass.IsNull())

	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		InSoftWidgetClass.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[InSoftWidgetClass,this,InStackTag,AsyncPushStateCallBack]()
			{
				UClass* LoadedWidgetClass = InSoftWidgetClass.Get();

				check(LoadedWidgetClass);
				check(CreatedPrimaryLayout);

				UCommonActivatableWidgetContainerBase* FoundWidgetStack = CreatedPrimaryLayout->GetWidgetStackByTag(
					InStackTag);

				UWidget_ActivatableBase* CreatedWidget = FoundWidgetStack->AddWidget<UWidget_ActivatableBase>(
					LoadedWidgetClass,
					[AsyncPushStateCallBack](UWidget_ActivatableBase& CreatedWidgetInstance)
					{
						AsyncPushStateCallBack(EAsyncPushWidgetState::OnCreatedBeforePush, &CreatedWidgetInstance);
					}
				);
				AsyncPushStateCallBack(EAsyncPushWidgetState::AfterPush, CreatedWidget);
			}
		)
	);
}
