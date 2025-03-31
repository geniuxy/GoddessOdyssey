#pragma once

#include "GoddessEnumTypes.generated.h"

UENUM()
enum class EGoddessConfirmType:uint8
{
	Yes,
	No
};

UENUM()
enum class EGoddessValidType:uint8
{
	Valid,
	Invalid
};

UENUM()
enum class EGoddessSuccessType:uint8
{
	Successful,
	Failed
};

UENUM()
enum class EGoddesssCountDownActionInput : uint8
{
	Start,
	Cancel
};

UENUM()
enum class EGoddesssCountDownActionOutput : uint8
{
	Updated,
	Completed,
	Cancelled
};

UENUM(BlueprintType)
enum class EGoddessGameDifficulty: uint8
{
	Easy,
	Normal,
	Hard,
	VeryHard
};

UENUM(BlueprintType)
enum class EGoddessInputMode : uint8
{
	GameOnly,
	UIOnly
};
