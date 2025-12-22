// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonListView.h"
#include "GameUIListView.generated.h"

class UDataAsset_DataListEntryMapping;
/**
 * 
 */
UCLASS()
class GAMEUI_API UGameUIListView : public UCommonListView
{
	GENERATED_BODY()

protected:
	//~ Begin UCommonListView interface
	virtual UUserWidget& OnGenerateEntryWidgetInternal(
		UObject* Item,
		TSubclassOf<UUserWidget> DesiredEntryClass,
		const TSharedRef<STableViewBase>& OwnerTable
	) override;
	//~ End UCommonListView interface

private:
#if WITH_EDITOR
	virtual void ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const override;
#endif

	UPROPERTY(EditAnywhere, Category="GameUI|ListView")
	TObjectPtr<UDataAsset_DataListEntryMapping> DataAsset_DataListEntryMapping;
};
