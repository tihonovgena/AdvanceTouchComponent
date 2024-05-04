#pragma once

#include "BlueprintTouchPins.generated.h"

// Touch pins touch for blueprint functions
UENUM()
namespace ETouchPins
{
	enum Type : uint8
	{
		Pressed = 0,
		Released = 5,
		Moved = 1
	};
}
