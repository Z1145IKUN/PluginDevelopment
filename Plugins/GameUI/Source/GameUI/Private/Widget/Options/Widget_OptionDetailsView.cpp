// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/Widget_OptionDetailsView.h"

#include "CommonLazyImage.h"
#include "CommonRichTextBlock.h"
#include "CommonTextBlock.h"
#include "Widget/Options/DataObject/ListDataObject_Base.h"

void UWidget_OptionDetailsView::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ClearOptionDetailsView();
}

void UWidget_OptionDetailsView::UpdateOptionDetailsView(const UListDataObject_Base* InListDataObject) const
{
	if (!InListDataObject)
	{
		return;
	}

	CommonTextBlock_Title->SetText(InListDataObject->GetDataDisplayName());

	if (!InListDataObject->GetSoftDescriptionImage().IsNull())
	{
		CommonLazyImage_DescriptionImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		CommonLazyImage_DescriptionImage->SetBrushFromLazyTexture(InListDataObject->GetSoftDescriptionImage());
	}
	else
	{
		CommonLazyImage_DescriptionImage->SetVisibility(ESlateVisibility::Collapsed);
	}
	CommonRichTextBlock_Description->SetText(InListDataObject->GetDescriptionRichText());
	CommonRichTextBlock_DynamicDetails->SetText(FText::GetEmpty());
	CommonRichTextBlock_DisabledReason->SetText(InListDataObject->GetDisableRichText());
}

void UWidget_OptionDetailsView::ClearOptionDetailsView() const
{
	CommonTextBlock_Title->SetText(FText::GetEmpty());
	CommonLazyImage_DescriptionImage->SetVisibility(ESlateVisibility::Collapsed);
	CommonRichTextBlock_Description->SetText(FText::GetEmpty());
	CommonRichTextBlock_DynamicDetails->SetText(FText::GetEmpty());
	CommonRichTextBlock_DisabledReason->SetText(FText::GetEmpty());
}
