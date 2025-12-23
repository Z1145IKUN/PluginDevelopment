// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/ListEntry/Widget_ListEntry_String.h"

#include "Widget/Component/GameUIRotator.h"
#include "Widget/Options/DataObject/ListDataObject_String.h"
#include "Widget/Component/GameUIButtonBase.h"

void UWidget_ListEntry_String::OnListDataObjectSet(UListDataObject_Base* InListDataObject)
{
	Super::OnListDataObjectSet(InListDataObject);

	StringListDataObject = CastChecked<UListDataObject_String>(InListDataObject);

	CommonRotator_Options->PopulateTextLabels(StringListDataObject->GetAvailableOptionsTextArray());
	CommonRotator_Options->SetSelectedOptionByText(StringListDataObject->GetCurrentDisplayText());
	CommonRotator_Options->OnClicked().AddLambda(
		[this]()
		{
			SelectedThisEntryWidget();
		}
	);
}

void UWidget_ListEntry_String::OnListDataObjectModified(UListDataObject_Base* ModifiedData,
                                                        EOptionsListDataModifyReason ModifyReason)
{
	if (StringListDataObject)
	{
		CommonRotator_Options->SetSelectedOptionByText(StringListDataObject->GetCurrentDisplayText());
	}
}

void UWidget_ListEntry_String::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CommonButton_Previous->OnClicked().AddUObject(this, &ThisClass::OnPreviousButtonClicked);
	CommonButton_Next->OnClicked().AddUObject(this, &ThisClass::OnNextButtonClicked);
}

void UWidget_ListEntry_String::OnPreviousButtonClicked()
{
	if (StringListDataObject)
	{
		StringListDataObject->AdvanceToPreviousOption();
	}
	SelectedThisEntryWidget();
}

void UWidget_ListEntry_String::OnNextButtonClicked()
{
	if (StringListDataObject)
	{
		StringListDataObject->AdvanceToNextOption();
	}
	SelectedThisEntryWidget();
}
