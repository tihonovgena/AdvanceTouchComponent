#pragma once

#include "ATCTouchData.generated.h"

class UAdvanceTouchComponent;

USTRUCT()
struct FATCTouchData
{
	GENERATED_BODY()

	int32 Handle = 0;
	TWeakObjectPtr<UAdvanceTouchComponent> TouchComponent;
	
};