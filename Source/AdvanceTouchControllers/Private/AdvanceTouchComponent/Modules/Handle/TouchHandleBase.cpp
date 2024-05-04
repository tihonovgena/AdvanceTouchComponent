// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "AdvanceTouchComponent/Modules/Handle/TouchHandleBase.h"

void UTouchHandleBase::InputTouch(EInputEvent Type, const FVector2D& TouchLocation, FDateTime DeviceTimestamp)
{
	switch (Type)
	{
		case EInputEvent::IE_Pressed:
			TouchBegun(TouchLocation, DeviceTimestamp);
			break;

		case EInputEvent::IE_Repeat:
			TouchMoved(TouchLocation, DeviceTimestamp);
			break;
		
		case EInputEvent::IE_Released:
			TouchEnded(TouchLocation, DeviceTimestamp);
			break;
		
		default:
			break;
	}
}

void UTouchHandleBase::TouchBegun(const FVector2D& TouchLocation, FDateTime DeviceTimestamp)
{
}

void UTouchHandleBase::TouchMoved(const FVector2D& TouchLocation, FDateTime DeviceTimestamp)
{
}

void UTouchHandleBase::TouchEnded(const FVector2D& TouchLocation, FDateTime DeviceTimestamp)
{
}
