// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "AdvanceTouchComponent/StickRectBorderComponent.h"

#include "AdvanceTouchComponent/Modules/Border/TouchRectBorder.h"

UStickRectBorderComponent::UStickRectBorderComponent()
{
	RectSize = FVector2D(200.f, 200.f);
	
	ControllerBorderClass = UTouchRectBorder::StaticClass();
}

void UStickRectBorderComponent::BeginPlay()
{
	Super::BeginPlay();

	UTouchRectBorder* RectBorder = Cast<UTouchRectBorder>(GetControllerBorder());
	if (RectBorder)
	{
		RectBorder->SetRectSize(RectSize);
	}
	
}

