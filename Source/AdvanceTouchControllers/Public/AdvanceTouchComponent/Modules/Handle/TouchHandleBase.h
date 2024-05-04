// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AdvanceTouchComponent/Modules/TouchControllerBase.h"
#include "TouchHandleBase.generated.h"

UCLASS(Abstract, Blueprintable)
class ADVANCETOUCHCONTROLLERS_API UTouchHandleBase : public UTouchControllerBase
{
	GENERATED_BODY()

public:
	void InputTouch(EInputEvent Type, const FVector2D& TouchLocation, FDateTime DeviceTimestamp);

protected:	
	virtual void TouchBegun(const FVector2D& TouchLocation, FDateTime DeviceTimestamp);
	virtual void TouchMoved(const FVector2D& TouchLocation, FDateTime DeviceTimestamp);
	virtual void TouchEnded(const FVector2D& TouchLocation, FDateTime DeviceTimestamp);
	
};
