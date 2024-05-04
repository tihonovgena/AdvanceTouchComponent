// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "TouchControllerWidget/TouchControllerWidgetBase.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "Misc/ViewportHelper.h"

void UTouchControllerWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	OnControllerUpdateRequest.AddDynamic(this, &UTouchControllerWidgetBase::OnUpdateControllerWidget);
}

void UTouchControllerWidgetBase::SetupBoxSize(USizeBox* SizeBox)
{
	ControllerSizeBox = SizeBox;
	
	UCanvasPanelSlot* ControlGridSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ControllerSizeBox);
	if (ControlGridSlot)
	{
		ControlGridSlot->SetAlignment(UViewportHelper::GetAlignmentValue(EControllerAlignment::Middle));
	}
	
	OnControllerUpdateRequest.Broadcast();
}

void UTouchControllerWidgetBase::SetControllerSize(const FVector2D& Size)
{
	ControllerSize = Size;
	OnControllerUpdateRequest.Broadcast();
}

void UTouchControllerWidgetBase::SetControllerPosition(const FVector2D& Position)
{
	ControllerPosition = Position;
	OnControllerUpdateRequest.Broadcast();
}

void UTouchControllerWidgetBase::OnUpdateControllerWidget()
{
	UpdateSizeBox();
}

void UTouchControllerWidgetBase::UpdateSizeBox()
{
	if (IsValid(ControllerSizeBox))
	{
		ControllerSizeBox->SetWidthOverride(ControllerSize.X);
		ControllerSizeBox->SetHeightOverride(ControllerSize.Y);
		ControllerSizeBox->SetRenderTranslation(ControllerPosition);
	}
}

void UTouchControllerWidgetBase::PaintDebugGeometry(FSlateWindowElementList& OutDrawElements,
                                            int32 LayerId, const TArray<FVector2D>& Points) const
{
	const FPaintGeometry PaintGeometry;
	FSlateDrawElement::MakeLines(OutDrawElements, LayerId, PaintGeometry, Points,
		ESlateDrawEffect::None, FLinearColor::Red);
	
}

int32 UTouchControllerWidgetBase::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	
	// Draw debug border if bEnableDebug
	if (bEnableDebug)
	{
		PaintDebugGeometry(OutDrawElements, LayerId, DebugGeometryPoints);
	}
	
	return Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle,
							  bParentEnabled);
}