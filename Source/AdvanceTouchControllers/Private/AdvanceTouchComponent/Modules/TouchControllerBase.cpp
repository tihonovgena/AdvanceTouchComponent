// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "AdvanceTouchComponent/Modules/TouchControllerBase.h"

#include "UnrealClient.h"
#include "Misc/ViewportHelper.h"
#include "TouchControllerWidget/TouchControllerWidgetBase.h"

DEFINE_LOG_CATEGORY(AdvanceTouchController);

UTouchControllerBase::UTouchControllerBase()
{
	TouchControllerWidgetClass = UTouchControllerWidgetBase::StaticClass();
}

void UTouchControllerBase::RunControllerModule()
{
	BindResizeEvent();
	CreateControllerWidget(TouchControllerWidgetClass);
}

TArray<FVector2D> UTouchControllerBase::GetDebugGeometryPoints()
{
	TArray<FVector2D> Points;
	return Points;
}

void UTouchControllerBase::OnViewportSizeChanged(FViewport* Viewport, uint32 Index)
{
	OnUpdateControllerVisual.Broadcast();
	UpdateWidgetProperties();
}

FVector2D UTouchControllerBase::GetControllerOffset() const
{
	return ControllerOffset * UViewportHelper::GetDPIScale(GetWorld());
}

FVector2D UTouchControllerBase::GetControllerSize() const
{
	return FVector2D();
}

FVector2D UTouchControllerBase::GetScaledControllerSize() const
{
	const float DPIScale = UViewportHelper::GetDPIScale(GetWorld());
	return GetControllerSize() * DPIScale;;
}

FVector2D UTouchControllerBase::GetControllerPosition() const
{
	return UViewportHelper::GetRectAlignmentPosition(GetWorld(), GetScaledControllerSize(), GetAlignment());
}

FVector2D UTouchControllerBase::GetAdjustedControllerPosition() const
{
	FVector2D ControlPosition = GetControllerPosition();
	UViewportHelper::AdjustPositionWithOffset(ControlPosition, GetControllerOffset(), GetAlignment());
	return ControlPosition;
}

FVector2D UTouchControllerBase::GetBorderPosition() const
{
	return GetControllerPosition();
}

void UTouchControllerBase::BindResizeEvent()
{
	const UWorld* World = GetWorld();
	if (World)
	{
		const FViewport* Viewport = UViewportHelper::GetViewport(GetWorld());
		if (Viewport)
		{
			Viewport->ViewportResizedEvent.AddUObject(this, &UTouchControllerBase::OnViewportSizeChanged);
		}
	}
}


void UTouchControllerBase::CreateControllerWidget(TSubclassOf<UUserWidget> WidgetClass)
{
	if (WidgetClass)
	{
		UUserWidget* Widget = CreateWidget(GetWorld(), WidgetClass);
		TouchControllerWidget = Cast<UTouchControllerWidgetBase>(Widget);
		UpdateWidgetProperties();
		TouchControllerWidget->AddToViewport(0);
	}
	else
	{
		UE_LOG(AdvanceTouchController, Warning, TEXT("%s doesn't have widget class"), *this->GetName())
	}
	
}

void UTouchControllerBase::UpdateWidgetProperties()
{
	if (IsValid(TouchControllerWidget))
	{
		TouchControllerWidget->SetDebugGeometryPoints(GetDebugGeometryPoints());
		TouchControllerWidget->SetEnableDebug(bShowDebug);
		
		const FVector2D Position = GetAdjustedControllerPosition() / UViewportHelper::GetDPIScale(GetWorld());
		TouchControllerWidget->SetControllerPosition(Position);

		TouchControllerWidget->SetControllerSize(GetControllerSize());
	}
}
