// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "AdvanceTouchComponent/Modules/Border/TouchCircleBorder.h"

#include "Misc/DrawGeometryHelper.h"

UTouchCircleBorder::UTouchCircleBorder()
{
	NumCircleSegments = 12;
	CircleRadius = 50.f;
}

FVector2D UTouchCircleBorder::GetControllerSize() const
{
	return FVector2D{CircleRadius * 2};
}

float UTouchCircleBorder::GetScaledRadius() const
{
	return GetScaledControllerSize().X / 2;
}

bool UTouchCircleBorder::IsTouchInputInBorder(const FVector2D& TouchLocation)
{
	const float DistanceSquare = FVector2D::DistSquared(TouchLocation, GetAdjustedControllerPosition());
	return DistanceSquare <= FMath::Square(GetScaledRadius());
}

TArray<FVector2D> UTouchCircleBorder::GetDebugGeometryPoints()
{
	return UDrawGeometryHelper::DrawCircle(GetScaledRadius(), NumCircleSegments, GetAdjustedControllerPosition());
}
