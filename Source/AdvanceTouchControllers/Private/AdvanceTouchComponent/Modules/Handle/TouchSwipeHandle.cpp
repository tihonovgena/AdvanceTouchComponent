// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "AdvanceTouchComponent/Modules/Handle/TouchSwipeHandle.h"

#include "Misc/TimeHelper.h"

UTouchSwipeHandle::UTouchSwipeHandle()
{
	DetectionSwipeTime = 0.3;
}

void UTouchSwipeHandle::TouchBegun(const FVector2D& TouchLocation, FDateTime DeviceTimestamp)
{
	Super::TouchBegun(TouchLocation, DeviceTimestamp);
	
	TouchBegunDateTime = DeviceTimestamp;
	BegunLocation = TouchLocation;
}

void UTouchSwipeHandle::TouchEnded(const FVector2D& TouchLocation, FDateTime DeviceTimestamp)
{
	Super::TouchEnded(TouchLocation, DeviceTimestamp);
	
	FVector2D SwipeDirection = TouchLocation - BegunLocation;
	const float ElapsedTimeInSeconds = UTimeHelper::GetTotalSecondsBetweenDate(TouchBegunDateTime, DeviceTimestamp);
	if (ElapsedTimeInSeconds <= DetectionSwipeTime && !SwipeDirection.IsNearlyZero())
	{
		SwipeDirection.Normalize();
		const FVector2D RoundedVector = SwipeDirection.RoundToVector();
		
		if (RoundedVector == FVector2D(0, -1))
		{
			OnHandleSwipeUp.Broadcast();
		}
		else if (RoundedVector == FVector2D(0, 1))
		{
			OnHandleSwipeDown.Broadcast();
		}
		else if (RoundedVector == FVector2D(-1, 0))
		{
			OnHandleSwipeLeft.Broadcast();
		}
		else if (RoundedVector == FVector2D(1, 0))
		{
			OnHandleSwipeRight.Broadcast();
		}
	}
}
