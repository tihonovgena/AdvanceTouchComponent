// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "AdvanceTouchComponent/Modules/Border/TouchRectBorder.h"

#include "Misc/DrawGeometryHelper.h"
#include "Misc/ViewportHelper.h"

UTouchRectBorder::UTouchRectBorder()
{
	RectSize = FVector2D(300.f, 300.f);
}

FVector2D UTouchRectBorder::GetControllerSize() const
{
	return RectSize;
}

bool UTouchRectBorder::IsTouchInputInBorder(const FVector2D& TouchLocation)
{
	const FVector2D ScaledRecSize = GetScaledControllerSize();
	const double RectWidth = ScaledRecSize.X / 2.f;
	const double RectHeight = ScaledRecSize.Y / 2.f;

	const double WidthSubLocation = FMath::Abs(TouchLocation.X - GetAdjustedControllerPosition().X);
	const double HeightSubLocation = FMath::Abs(TouchLocation.Y - GetAdjustedControllerPosition().Y);
	
	return WidthSubLocation  <= RectWidth && HeightSubLocation  <= RectHeight;
}

TArray<FVector2D> UTouchRectBorder::GetDebugGeometryPoints()
{
	return UDrawGeometryHelper::DrawRect(GetScaledControllerSize(), GetAdjustedControllerPosition());
}