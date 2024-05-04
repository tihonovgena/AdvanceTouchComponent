// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "AdvanceTouchComponent/Modules/Border/TouchFullScreenBorder.h"

#include "Misc/ViewportHelper.h"

FVector2D UTouchFullScreenBorder::GetControllerSize() const
{
	const float DPIScale = UViewportHelper::GetDPIScale(GetWorld());
	return UViewportHelper::GetViewportSize(GetWorld()) / DPIScale;
}

bool UTouchFullScreenBorder::IsTouchInputInBorder(const FVector2D& TouchLocation)
{
	return true;
}
