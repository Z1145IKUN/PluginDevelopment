// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/GameUISubsystem.h"

#include "GameUIGameplayTags.h"
#include "Widget/Widget_ActivatableBase.h"
#include "Widget/Widget_PrimaryLayout.h"
#include "Engine/AssetManager.h"
#include "FunctionLibrary/GameUIFunctionLibrary.h"
#include "Widget/Widget_ConfirmScreen.h"
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

void UGameUISubsystem::PushConfirmScreenToModalStackAsync(EConfirmScreenType InScreenType, const FText& InScreenTitle,
                                                          const FText& InScreenMessage,
                                                          TFunction<void(EConfirmScreenButtonType)>
                                                          ScreenButtonCallBack)
{
	UConfirmScreenInfoObject* CreatedConfirmScreenInfoObject = nullptr;
	switch (InScreenType)
	{
	case EConfirmScreenType::OK:
		CreatedConfirmScreenInfoObject = UConfirmScreenInfoObject::CreateOkScreen(InScreenTitle, InScreenMessage);
		break;
	case EConfirmScreenType::YesNo:
		CreatedConfirmScreenInfoObject = UConfirmScreenInfoObject::CreateYesNoScreen(InScreenTitle, InScreenMessage);
		break;
	case EConfirmScreenType::OkCancel:
		CreatedConfirmScreenInfoObject = UConfirmScreenInfoObject::CreateOkCancelScreen(InScreenTitle, InScreenMessage);
	case EConfirmScreenType::UnKnown:
		break;
	default:
		break;
	}

	check(CreatedConfirmScreenInfoObject);

	PushSoftWidgetToStack(
		GameUIGameplayTags::GameUI_WidgetStack_Modal,
		UGameUIFunctionLibrary::GetSoftWidgetClassByTag(GameUIGameplayTags::GameUI_Widget_ConfirmScreen),
		[CreatedConfirmScreenInfoObject,ScreenButtonCallBack]
	(EAsyncPushWidgetState InAsyncPushState, UWidget_ActivatableBase* PushedWidget)
		{
			if (InAsyncPushState == EAsyncPushWidgetState::OnCreatedBeforePush)
			{
				UWidget_ConfirmScreen* CreatedConfirmScreen = CastChecked<UWidget_ConfirmScreen>(PushedWidget);
				CreatedConfirmScreen->InitConfirmScreen(CreatedConfirmScreenInfoObject, ScreenButtonCallBack);
			}
		}
	);
}
