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
