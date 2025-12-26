// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/Options/Widget_TabListWidgetBase.h"

#include "Editor/WidgetCompilerLog.h"
#include "Widget/Component/GameUIButtonBase.h"

UWidget_TabListWidgetBase::UWidget_TabListWidgetBase()
{
	DebugEditorPreviewTabCount = 4;
}

void UWidget_TabListWidgetBase::RequestRegisterTab(const FName& InTabID, const FText& InTabDisplayName)
{
	RegisterTab(InTabID, TabButtonEntryWidgetClass, nullptr);

	if (UGameUIButtonBase* FoundButton = Cast<UGameUIButtonBase>(GetTabButtonBaseByID(InTabID)))
	{
		FoundButton->SetButtonText(InTabDisplayName);
	}
}

#if WITH_EDITOR
void UWidget_TabListWidgetBase::ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);

	if (!TabButtonEntryWidgetClass)
	{
		CompileLog.Error(
			FText::FromString(
				TEXT("the variable TabButtonEntryWidgetClass has not valid entry specified")
				+ GetClass()->GetName()
				+ TEXT("need a valid entry widget class to function properly")
			)
		);
	}
}
#endif
