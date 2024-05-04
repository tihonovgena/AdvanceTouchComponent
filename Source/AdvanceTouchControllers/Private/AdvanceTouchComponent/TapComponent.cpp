// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "AdvanceTouchComponent/TapComponent.h"

#include "AdvanceTouchComponent/Modules/Border/TouchFullScreenBorder.h"
#include "AdvanceTouchComponent/Modules/Handle/TouchTapHandle.h"

UTapComponent::UTapComponent()
{
	Alignment = EControllerAlignment::Middle;
	ControllerBorderClass = UTouchFullScreenBorder::StaticClass();
	ControllerHandleClass = UTouchTapHandle::StaticClass();
	DetectionTapTime = 0.1f;
	DetectionDoubleTapTime = 0.2f;
}

void UTapComponent::BeginPlay()
{
	Super::BeginPlay();
	
	UTouchTapHandle* TapHandle = Cast<UTouchTapHandle>(GetControllerHandle());
	if (TapHandle)
	{
		TapHandle->SetDetectionTapTime(DetectionTapTime);
		TapHandle->SetDetectionDoubleTapTime(DetectionDoubleTapTime);
		TapHandle->OnTap.AddDynamic(this, &UTapComponent::OnHandleTap);
		TapHandle->OnDoubleTap.AddDynamic(this, &UTapComponent::OnHandleDoubleTap);
	}
}

void UTapComponent::OnHandleTap(FVector2D TapLocation)
{
	OnTap.Broadcast(TapLocation);
}

void UTapComponent::OnHandleDoubleTap(FVector2D TapLocation)
{
	OnDoubleTap.Broadcast(TapLocation);
}
