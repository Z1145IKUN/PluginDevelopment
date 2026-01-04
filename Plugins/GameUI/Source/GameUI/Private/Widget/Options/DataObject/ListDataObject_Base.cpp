// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Options/DataObject/ListDataObject_Base.h"
#include "DeveloperSettings/GameUIGameUserSettings.h"

TArray<UListDataObject_Base*> UListDataObject_Base::GetAllChildListData() const
{
	return TArray<UListDataObject_Base*>();
}

bool UListDataObject_Base::HasChildListData() const
{
	return false;
}

void UListDataObject_Base::InitDataObject()
{
	OnDataListObjectInitialized();
}

void UListDataObject_Base::SetShouldApplySettingsImmediately(bool InShouldApplySettingsImmediately)
{
	bShouldApplyChangesImmediately = InShouldApplySettingsImmediately;
}

bool UListDataObject_Base::HasDefaultValue() const
{
	return false;
}

bool UListDataObject_Base::CanResetBackToDefaultValue() const
{
	return false;
}

bool UListDataObject_Base::TryResetBackToDefaultValue()
{
	return false;
}

void UListDataObject_Base::AddEditCondition(const FOptionsDataEditConditionDescriptor& InEditCondition)
{
	EditConditionDescriptorArray.Add(InEditCondition);
}

bool UListDataObject_Base::IsDataCurrentlyEditable()
{
	bool bIsEditable = true;

	if (EditConditionDescriptorArray.IsEmpty())
	{
		return bIsEditable;
	}

	FString CachedDisabledRichReason;

	for (const FOptionsDataEditConditionDescriptor& EditCondition : EditConditionDescriptorArray)
	{
		if (!EditCondition.IsValid() || EditCondition.IsEditConditionMet())
		{
			continue;
		}

		bIsEditable = false;

		CachedDisabledRichReason.Append(EditCondition.GetDisabledRichReason());

		SetDisableRichText(FText::FromString(CachedDisabledRichReason));

		//If it is found that the data is in an uneditable state, then change the data to ForceStringValue
		if (EditCondition.HasForceStringValue())
		{
			const FString ForcedStringValue = EditCondition.GetDisabledForcedStringValue();

			//if current value this data object has can be set to the force value 
			if (CanSetToForceStringValue(ForcedStringValue))
			{
				OnSetToForceStringValue(ForcedStringValue);
			}
		}
	}

	return bIsEditable;
}

void UListDataObject_Base::AddEditDependencyData(UListDataObject_Base* InDependencyData)
{
	if (!InDependencyData->OnListDataModified.IsBoundToObject(this))
	{
		InDependencyData->OnListDataModified.AddUObject(this, &ThisClass::OnEditDependencyDataModified);
	}
}

void UListDataObject_Base::OnDataListObjectInitialized()
{
}

void UListDataObject_Base::NotifyListDataModified(UListDataObject_Base* ModifiedListData,
                                                  EOptionsListDataModifyReason ModifyReason)
{
	OnListDataModified.Broadcast(ModifiedListData, ModifyReason);

	if (bShouldApplyChangesImmediately)
	{
		UGameUIGameUserSettings::Get()->ApplySettings(true);
	}
}

bool UListDataObject_Base::CanSetToForceStringValue(const FString& InForceStringValue) const
{
	return false;
}

void UListDataObject_Base::OnSetToForceStringValue(const FString& InForceStringValue)
{
}

void UListDataObject_Base::OnEditDependencyDataModified(
	UListDataObject_Base* ModifiedDependencyData,
	EOptionsListDataModifyReason ModifyReason)
{
	OnDependencyDataModified.Broadcast(ModifiedDependencyData, ModifyReason);
}
