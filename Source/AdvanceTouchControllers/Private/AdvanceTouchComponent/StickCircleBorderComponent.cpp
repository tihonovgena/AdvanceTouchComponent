// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "AdvanceTouchComponent/StickCircleBorderComponent.h"

#include "AdvanceTouchComponent/Modules/Border/TouchCircleBorder.h"

UStickCircleBorderComponent::UStickCircleBorderComponent()
{
	BorderRadius = 175.f;

	ControllerBorderClass = UTouchCircleBorder::StaticClass();
}

void UStickCircleBorderComponent::BeginPlay()
{
	Super::BeginPlay();
	
	UTouchCircleBorder* CircleBorder = Cast<UTouchCircleBorder>(GetControllerBorder());
	if (CircleBorder)
	{
		CircleBorder->SetRadius(BorderRadius);
	}
	
}

