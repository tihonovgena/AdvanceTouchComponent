// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "AdvanceTouchComponent/RectButtonComponent.h"

#include "AdvanceTouchComponent/Modules/Border/TouchRectBorder.h"
#include "AdvanceTouchComponent/Modules/Handle/TouchButtonHandle.h"

URectButtonComponent::URectButtonComponent()
{
	ButtonSize = FVector2D(100.f, 100.f);
	
	Alignment = EControllerAlignment::Middle;
	ControllerBorderClass = UTouchRectBorder::StaticClass();
	ControllerHandleClass = UTouchButtonHandle::StaticClass();
}


void URectButtonComponent::BeginPlay()
{
	Super::BeginPlay();

	UTouchRectBorder* TouchRectBorder = Cast<UTouchRectBorder>(GetControllerBorder());
	if (TouchRectBorder)
	{
		TouchRectBorder->SetRectSize(ButtonSize);
	}

	UTouchButtonHandle* ButtonHandle = Cast<UTouchButtonHandle>(GetControllerHandle());
	if (ButtonHandle)
	{
		ButtonHandle->SetButtonSize(ButtonSize);
	}
	
}
