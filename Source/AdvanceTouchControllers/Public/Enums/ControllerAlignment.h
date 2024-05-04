#pragma once

#include "ControllerAlignment.generated.h"

UENUM()
namespace EControllerAlignment
{
	enum Type : uint8
	{
		Middle,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};
}
