#pragma once

UENUM(BlueprintType)
enum class EConfirmScreenType : uint8
{
	OK,
	YesNo,
	OkCancel,
	UnKnown UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EConfirmScreenButtonType : uint8
{
	Confirmed,
	Canceled,
	Closed,
	Unknown UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EOptionsListDataModifyReason : uint8
{
	DirectlyModify,
	DependencyModify,
	ResetToDefault
};