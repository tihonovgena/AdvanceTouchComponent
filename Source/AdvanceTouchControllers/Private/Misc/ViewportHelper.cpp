// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "Misc/ViewportHelper.h"
#include "Misc/AlignmentConstants.h"

#include "Engine/UserInterfaceSettings.h"

FVector2D UViewportHelper::GetAlignmentPosition(const UWorld* World, const EControllerAlignment::Type Alignment)
{
	const FVector2D ViewportSize = GetViewportSize(World);

	const FVector2D AlignmentValue = GetAlignmentValue(Alignment);
	
	return FVector2D(ViewportSize.X * AlignmentValue.X, ViewportSize.Y * AlignmentValue.Y);
}

FVector2D UViewportHelper::GetRectAlignmentPosition(const UWorld* World, const FVector2D& Size,
	const EControllerAlignment::Type Alignment)
{
	FVector2D AlignmentPosition = GetAlignmentPosition(World, Alignment);

	// We don't do offset if it is middle position
	if (Alignment == EControllerAlignment::Middle)
	{
		return AlignmentPosition;
	}
	
	const FVector2D HalfSize = Size / 2.0;
	AdjustPositionWithOffset(AlignmentPosition, HalfSize, Alignment);
	
	return AlignmentPosition;
}

FVector2D UViewportHelper::GetCircleAlignmentPosition(const UWorld* World, const float Radius,
	const EControllerAlignment::Type Alignment)
{
	FVector2D AlignmentPosition = GetAlignmentPosition(World, Alignment);

	// We don't do offset if it is middle position
	if (Alignment == EControllerAlignment::Middle)
	{
		return AlignmentPosition;
	}
	
	const FVector2D RadiusOffset = FVector2D(Radius, Radius);
	AdjustPositionWithOffset(AlignmentPosition, RadiusOffset, Alignment);
	
	return AlignmentPosition;
}

FVector2D UViewportHelper::GetAlignmentValue(const EControllerAlignment::Type Alignment)
{
	return AMC_ALIGNMENTS_ARRAY[Alignment];
}

void UViewportHelper::AdjustPositionWithOffset(FVector2D& AdjustPosition, const FVector2D Offset,
	const EControllerAlignment::Type Alignment)
{
	const FVector2D AlignmentValue = GetAlignmentValue(Alignment);
	
	AdjustPosition.X = (AdjustPosition.X) + (AlignmentValue.X == 0 ? Offset.X : -Offset.X);
	AdjustPosition.Y = (AdjustPosition.Y) + (AlignmentValue.Y == 0 ? Offset.Y : -Offset.Y);
}

FViewport* UViewportHelper::GetViewport(const UWorld* World)
{
	const UGameViewportClient* GameViewportClient = GetGameViewportClient(World);
	if(!IsValid(GameViewportClient)) return nullptr;
	
	return GameViewportClient->Viewport;
}

UGameViewportClient* UViewportHelper::GetGameViewportClient(const UWorld* World)
{
	if (World)
	{
		return World->GetGameViewport();
	}
	
	return nullptr;
}

FVector2D UViewportHelper::GetViewportSize(const UWorld* World)
{
	const FViewport* Viewport = GetViewport(World);
	if (Viewport)
	{
		return FVector2D(Viewport->GetSizeXY().X, Viewport->GetSizeXY().Y);
	}
	return FVector2D();
}

float UViewportHelper::GetDPIScale(const UWorld* World)
{
	const FViewport* Viewport = GetViewport(World);
	if (Viewport)
	{
		const FIntPoint ViewportSize = Viewport->GetSizeXY();
		return GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(ViewportSize);
	}
	
	return 0.f;
}
