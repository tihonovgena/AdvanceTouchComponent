// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "AdvanceTouchComponent/CircleButtonComponent.h"

#include "AdvanceTouchComponent/Modules/Border/TouchCircleBorder.h"
#include "AdvanceTouchComponent/Modules/Handle/TouchButtonHandle.h"


// Sets default values for this component's properties
UCircleButtonComponent::UCircleButtonComponent()
{
	ButtonRadius = 50.f;

	Alignment = EControllerAlignment::Middle;
	ControllerBorderClass = UTouchCircleBorder::StaticClass();
	ControllerHandleClass = UTouchButtonHandle::StaticClass();
}


void UCircleButtonComponent::BeginPlay()
{
	Super::BeginPlay();

	UTouchCircleBorder* TouchCircleBorder = Cast<UTouchCircleBorder>(GetControllerBorder());
	if (TouchCircleBorder)
	{
		TouchCircleBorder->SetRadius(ButtonRadius);
	}

	UTouchButtonHandle* ButtonHandle = Cast<UTouchButtonHandle>(GetControllerHandle());
	if (ButtonHandle)
	{
		ButtonHandle->SetButtonSize(FVector2D(ButtonRadius*2));
	}
	
}
