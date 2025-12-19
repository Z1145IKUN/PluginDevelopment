// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/Widget_TabListWidgetBase.h"

#include "Editor/WidgetCompilerLog.h"
#include "Widget/Component/GameUIButtonBase.h"

#if WITH_EDITOR
UWidget_TabListWidgetBase::UWidget_TabListWidgetBase()
{
	DebugEditorPreviewTabCount = 4;
}

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

