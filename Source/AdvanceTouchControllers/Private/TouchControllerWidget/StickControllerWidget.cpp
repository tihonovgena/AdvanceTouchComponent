// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "TouchControllerWidget/StickControllerWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Misc/ViewportHelper.h"
#include "Components/SizeBox.h"

class UCanvasPanelSlot;

void UStickControllerWidget::SetupBackgroundBoxSize(USizeBox* SizeBox)
{
	BackgroundSizeBox = SizeBox;
	
	UCanvasPanelSlot* ControlGridSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(BackgroundSizeBox);
	if (ControlGridSlot)
	{
		ControlGridSlot->SetAlignment(UViewportHelper::GetAlignmentValue(EControllerAlignment::Middle));
	}
	
	OnControllerUpdateRequest.Broadcast();
}

void UStickControllerWidget::OnUpdateControllerWidget()
{
	Super::OnUpdateControllerWidget();

	UpdateBackgroundSizeBox();
}

void UStickControllerWidget::UpdateBackgroundSizeBox()
{
	if (BackgroundSizeBox)
	{
		BackgroundSizeBox->SetWidthOverride(BackgroundSizeBoxSize.X);
		BackgroundSizeBox->SetHeightOverride(BackgroundSizeBoxSize.Y);
		BackgroundSizeBox->SetRenderTranslation(BackgroundSizeBoxPosition);
	}
}

void UStickControllerWidget::SetBackgroundSize(const FVector2D& Size)
{
	BackgroundSizeBoxSize = Size;
	OnControllerUpdateRequest.Broadcast();
}

void UStickControllerWidget::SetBackgroundPosition(const FVector2D& Position)
{
	BackgroundSizeBoxPosition = Position;
	OnControllerUpdateRequest.Broadcast();
}
