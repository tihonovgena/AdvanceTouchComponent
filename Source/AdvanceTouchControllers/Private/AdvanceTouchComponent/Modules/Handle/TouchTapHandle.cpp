// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "AdvanceTouchComponent/Modules/Handle/TouchTapHandle.h"

#include "Misc/TimeHelper.h"

void UTouchTapHandle::TouchBegun(const FVector2D& TouchLocation, FDateTime DeviceTimestamp)
{
	Super::TouchBegun(TouchLocation, DeviceTimestamp);

	TouchBegunDateTime = DeviceTimestamp;
}

void UTouchTapHandle::TouchEnded(const FVector2D& TouchLocation, FDateTime DeviceTimestamp)
{
	Super::TouchEnded(TouchLocation, DeviceTimestamp);
	
	const float ElapsedTimeInSeconds = UTimeHelper::GetTotalSecondsBetweenDate(TouchBegunDateTime, DeviceTimestamp);
	
	if (ElapsedTimeInSeconds <= DetectionTapTime)
	{
		if (DetectDoubleTap(TouchEndedDataTime, DeviceTimestamp))
		{
			OnDoubleTap.Broadcast(TouchLocation);
			TapAmount = 0;
		}
		else
		{
			TouchEndedDataTime = DeviceTimestamp;
			OnTap.Broadcast(TouchLocation);
			TapAmount = 1;
		}
	}
}

bool UTouchTapHandle::IsSecondTap() const
{
	return TapAmount == 1;
}

bool UTouchTapHandle::DetectDoubleTap(const FDateTime& LastEndTapDate, const FDateTime& CurrentEndTapDate) const
{
	if (IsSecondTap())
	{
		const float ElapsedTimeInSeconds = UTimeHelper::GetTotalSecondsBetweenDate(LastEndTapDate, CurrentEndTapDate);
		return ElapsedTimeInSeconds <= DetectionDoubleTapTime;
	}
	return false;
}
