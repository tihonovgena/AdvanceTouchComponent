// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "AdvanceTouchComponent/Modules/Handle/TouchStickHandle.h"

#include "AdvanceTouchComponent/Modules/Border/TouchBorderBase.h"
#include "Misc/DrawGeometryHelper.h"
#include "Misc/ViewportHelper.h"
#include "TouchControllerWidget/StickControllerWidget.h"

void UTouchStickHandle::TouchBegun(const FVector2D& TouchLocation, FDateTime DeviceTimestamp)
{
	Super::TouchBegun(TouchLocation, DeviceTimestamp);
	
	BegunLocation = TouchLocation;
	LastTouchLocation = TouchLocation;
	ClampTouchLocation(LastTouchLocation);
	
	UpdateWidgetProperties();

	float AxisX;
	float AxisY;
	CalculateAxis(GetBaseLocation(), TouchLocation, AxisX, AxisY);
	OnHandleStickBegun.Broadcast(TouchLocation, AxisX, AxisY);
}

void UTouchStickHandle::TouchMoved(const FVector2D& TouchLocation, FDateTime DeviceTimestamp)
{
	Super::TouchMoved(TouchLocation, DeviceTimestamp);

	LastTouchLocation = TouchLocation;
	ClampTouchLocation(LastTouchLocation);
	
	UpdateWidgetProperties();

	float AxisX;
	float AxisY;
	CalculateAxis(GetBaseLocation(), TouchLocation, AxisX, AxisY);
	OnHandleStickMoved.Broadcast(TouchLocation, AxisX, AxisY);
}

void UTouchStickHandle::TouchEnded(const FVector2D& TouchLocation, FDateTime DeviceTimestamp)
{
	Super::TouchEnded(TouchLocation, DeviceTimestamp);

	LastTouchLocation = GetBaseLocation();
	
	UpdateWidgetProperties();

	
	OnHandleStickEnded.Broadcast(TouchLocation, 0.f, 0.f);
}

void UTouchStickHandle::ClampTouchLocation(FVector2D& TouchLocation)
{
	const FVector2D BaseLocation = GetBaseLocation();
	const float Distance = FVector2D::Distance(BaseLocation, TouchLocation);
	if (Distance > HandleLength)
	{
		FVector2D Direction = TouchLocation - BaseLocation;
		Direction.Normalize();
		TouchLocation = BaseLocation + (HandleLength * Direction);
	}
}

FVector2D UTouchStickHandle::GetBaseLocation() const
{
	if (bUseBorderLocationAsStart)
	{
		return GetHandleBorderPosition();
	}
	else
	{
		if (BegunLocation.IsNearlyZero())
		{
			return GetHandleBorderPosition();
		}
		else
		{
			return BegunLocation;
		}
	}
}

FVector2D UTouchStickHandle::GetHandleBorderPosition() const
{
	if (TouchBorder.Get())
	{
		return TouchBorder.Get()->GetAdjustedControllerPosition();
	}
	return FVector2D();
}

TArray<FVector2D> UTouchStickHandle::GetDebugGeometryPoints()
{
	return UDrawGeometryHelper::DrawCircle(GetScaledRadius(), 12, GetControllerPosition());
}

void UTouchStickHandle::CalculateAxis(const FVector2D& StartLocation, const FVector2D& EndLocation, float& AxisX, float& AxisY) const
{
	const float DistanceX = EndLocation.X - StartLocation.X;
	AxisX = FMath::Clamp(DistanceX / HandleLength, -1.f, 1.f);

	const float DistanceY = (EndLocation.Y - StartLocation.Y) * -1.f;
	AxisY = FMath::Clamp(DistanceY / HandleLength, -1.f, 1.f);
}

FVector2D UTouchStickHandle::GetControllerPosition() const
{
	return LastTouchLocation;
}

FVector2D UTouchStickHandle::GetControllerSize() const
{
	return FVector2D(HandleRadius*2);
}

void UTouchStickHandle::SetTouchBorder(UTouchBorderBase* Border)
{
	TouchBorder = MakeWeakObjectPtr(Border);
}

float UTouchStickHandle::GetScaledRadius() const
{
	return GetScaledControllerSize().X / 2;
}

void UTouchStickHandle::UpdateWidgetProperties()
{
	Super::UpdateWidgetProperties();
	
	UStickControllerWidget* StickWidget = Cast<UStickControllerWidget>(GetControllerWidget());
	if (StickWidget)
	{
		StickWidget->SetBackgroundSize(StickBackgroundSize);
		const FVector2D ScaledBaseLocation = GetBaseLocation() / UViewportHelper::GetDPIScale(GetWorld());
		StickWidget->SetBackgroundPosition(ScaledBaseLocation);
	}
}

void UTouchStickHandle::InitFirstPosition(const FVector2D& Position)
{
	LastTouchLocation = Position;
	UpdateWidgetProperties();
}
