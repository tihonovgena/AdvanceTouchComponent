// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "AdvanceTouchComponent/Modules/Handle/TouchButtonHandle.h"

void UTouchButtonHandle::TouchBegun(const FVector2D& TouchLocation, FDateTime DeviceTimestamp)
{
	Super::TouchBegun(TouchLocation, DeviceTimestamp);
	OnHandleTouchBegun.Broadcast(TouchLocation);
}

void UTouchButtonHandle::TouchMoved(const FVector2D& TouchLocation, FDateTime DeviceTimestamp)
{
	Super::TouchMoved(TouchLocation, DeviceTimestamp);
	OnHandleTouchMoved.Broadcast(TouchLocation);
}

void UTouchButtonHandle::TouchEnded(const FVector2D& TouchLocation, FDateTime DeviceTimestamp)
{
	Super::TouchEnded(TouchLocation, DeviceTimestamp);
	OnHandleTouchEnded.Broadcast(TouchLocation);
}

FVector2D UTouchButtonHandle::GetControllerSize() const
{
	return ButtonSize;
}
