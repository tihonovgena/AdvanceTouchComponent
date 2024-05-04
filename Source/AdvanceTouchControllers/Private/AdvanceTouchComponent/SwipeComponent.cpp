// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "AdvanceTouchComponent/SwipeComponent.h"

#include "AdvanceTouchComponent/Modules/Border/TouchFullScreenBorder.h"
#include "AdvanceTouchComponent/Modules/Handle/TouchSwipeHandle.h"


// Sets default values for this component's properties
USwipeComponent::USwipeComponent()
{
	DetectionSwipeTime = 0.3;
	
	Alignment = EControllerAlignment::Middle;
	ControllerBorderClass = UTouchFullScreenBorder::StaticClass();
	ControllerHandleClass = UTouchSwipeHandle::StaticClass();
}


void USwipeComponent::BeginPlay()
{
	Super::BeginPlay();
	
	UTouchSwipeHandle* SwipeHandle = Cast<UTouchSwipeHandle>(GetControllerHandle());
	if (SwipeHandle)
	{
		SwipeHandle->SetDetectionSwipeTime(DetectionSwipeTime);
		SwipeHandle->OnHandleSwipeUp.AddDynamic(this, &USwipeComponent::OnHandleSwipeUp);
		SwipeHandle->OnHandleSwipeDown.AddDynamic(this, &USwipeComponent::OnHandleSwipeDown);
		SwipeHandle->OnHandleSwipeLeft.AddDynamic(this, &USwipeComponent::OnHandleSwipeLeft);
		SwipeHandle->OnHandleSwipeRight.AddDynamic(this, &USwipeComponent::OnHandleSwipeRight);
	}
}

void USwipeComponent::OnHandleSwipeUp()
{
	OnSwipeUp.Broadcast();
}

void USwipeComponent::OnHandleSwipeDown()
{
	OnSwipeDown.Broadcast();
}

void USwipeComponent::OnHandleSwipeLeft()
{
	OnSwipeLeft.Broadcast();
}

void USwipeComponent::OnHandleSwipeRight()
{
	OnSwipeRight.Broadcast();
}


