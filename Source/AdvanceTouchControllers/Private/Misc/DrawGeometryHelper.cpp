// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "Misc/DrawGeometryHelper.h"

TArray<FVector2D> UDrawGeometryHelper::DrawRect(const FVector2D& Size, const FVector2D& Center)
{
	const float RectWidth = Size.X / 2.f;
	const float RectHeight = Size.Y / 2.f;

	const FVector2D TopLeftCorner{Center.X - RectWidth, Center.Y - RectHeight};
	const FVector2D TopRightCorner{Center.X + RectWidth, Center.Y - RectHeight};
	const FVector2D BottomRightCorner{Center.X + RectWidth, Center.Y + RectHeight};
	const FVector2D BottomLeftCorner{Center.X - RectWidth, Center.Y + RectHeight};
	
	const TArray<FVector2D> Points
	{
		TopLeftCorner,
		TopRightCorner,
		BottomRightCorner,
		BottomLeftCorner,
		TopLeftCorner
	};
	
	return Points;
}

TArray<FVector2D> UDrawGeometryHelper::DrawCircle(const float Radius, const int32 NumCircleSegments, const FVector2D& Center)
{
	TArray<FVector2D> Points;
	
	const float AngleStep = 360.0f / NumCircleSegments;
	
	for (int32 i = 0; i < NumCircleSegments; ++i)
	{
		const float Angle = FMath::DegreesToRadians(AngleStep * i);
		
		const float X = Center.X + Radius * FMath::Cos(Angle);
		const float Y = Center.Y + Radius * FMath::Sin(Angle);
		
		Points.Add(FVector2D(X, Y));
	}

	const FVector2D FirstPoint = Points[0];
	Points.Add(FirstPoint);

	return Points;
}
