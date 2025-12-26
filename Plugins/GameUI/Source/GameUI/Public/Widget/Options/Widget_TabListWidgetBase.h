// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonTabListWidgetBase.h"
#include "Widget_TabListWidgetBase.generated.h"

class UGameUIButtonBase;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta=(DisableNativeTick))
class GAMEUI_API UWidget_TabListWidgetBase : public UCommonTabListWidgetBase
{
	GENERATED_BODY()

public:
	UWidget_TabListWidgetBase();

	void RequestRegisterTab(const FName& InTabID, const FText& InTabDisplayName);

private:
#if WITH_EDITOR
	virtual void ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const override;
#endif

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameUI|TabListWidget", meta=(AllowPrivateAccess = "true"))
	int32 DebugEditorPreviewTabCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameUI|TabListWidget", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UGameUIButtonBase> TabButtonEntryWidgetClass;
};
