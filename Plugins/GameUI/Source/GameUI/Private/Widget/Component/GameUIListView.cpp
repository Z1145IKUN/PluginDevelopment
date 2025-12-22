// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Component/GameUIListView.h"
#include "Editor/WidgetCompilerLog.h"
#include "DataAsset/DataAsset_DataListEntryMapping.h"
#include "Widget/Options/ListEntry/Widget_ListEntry_Base.h"
#include "Widget/Options/DataObject/ListDataObject_Base.h"


UUserWidget& UGameUIListView::OnGenerateEntryWidgetInternal(
	UObject* Item,
	TSubclassOf<UUserWidget> DesiredEntryClass,
	const TSharedRef<STableViewBase>& OwnerTable)
{
	if (IsDesignTime())
	{
		return Super::OnGenerateEntryWidgetInternal(Item, DesiredEntryClass, OwnerTable);
	}

	TSubclassOf<UWidget_ListEntry_Base> FoundWidgetClass = DataAsset_DataListEntryMapping->
		GetListEntryByListData(CastChecked<UListDataObject_Base>(Item));

	if (FoundWidgetClass)
	{
		return GenerateTypedEntry<UWidget_ListEntry_Base>(FoundWidgetClass, OwnerTable);
	}
	else
	{
		return Super::OnGenerateEntryWidgetInternal(Item, DesiredEntryClass, OwnerTable);
	}
}

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
