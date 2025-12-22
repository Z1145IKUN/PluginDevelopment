// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Component/GameUIListView.h"

#include "Editor/WidgetCompilerLog.h"

#if WITH_EDITOR
void UGameUIListView::ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);

	if (!DataAsset_DataListEntryMapping)
	{
		CompileLog.Error(
			FText::FromString(TEXT("the variable DataAsset_DataListEntryMapping has not valid data asset assign")
				+ GetClass()->GetName()
				+ TEXT("need a valid data asset to function properly"))
		);
	}
}
#endif
