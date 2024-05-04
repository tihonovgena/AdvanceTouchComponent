// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "AdvanceTouchComponent/StickComponent.h"

#include "AdvanceTouchComponent/Modules/Handle/TouchStickHandle.h"
#include "Blueprint/UserWidget.h"
#include "TouchControllerWidget/TouchControllerWidgetBase.h"

UStickComponent::UStickComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	HandleLength = 300.f;
	HandleRadius = 75.f;
	StickBackgroundSize = FVector2D(300.f, 300.f);
	bLockedStick = false;
	
	Alignment = EControllerAlignment::Middle;
	ControllerHandleClass = UTouchStickHandle::StaticClass();
	
}

void UStickComponent::BeginPlay()
{
	Super::BeginPlay();
	
	UTouchBorderBase* BorderBase = GetControllerBorder();
	if (BorderBase)
	{
		BorderBase->OnUpdateControllerVisual.AddDynamic(this, &UStickComponent::OnControllerBorderUpdateVisual);
	}
	
	UTouchStickHandle* StickHandle = Cast<UTouchStickHandle>(GetControllerHandle());
	if (StickHandle)
	{
		StickHandle->SetStickBackgroundSize(StickBackgroundSize);
		StickHandle->SetControllerAlignment(EControllerAlignment::TopLeft);
		StickHandle->SetControllerOffset(FVector2D(0.f, 0.f));
		StickHandle->SetHandleLength(HandleLength);
		StickHandle->SetEnableUseBorderLocationAsStart(bLockedStick);
		StickHandle->SetTouchBorder(GetControllerBorder());
		StickHandle->SetHandleRadius(HandleRadius);
		StickHandle->OnHandleStickBegun.AddDynamic(this, &UStickComponent::OnHandleTouchBegun);
		StickHandle->OnHandleStickMoved.AddDynamic(this, &UStickComponent::OnHandleTouchMoved);
		StickHandle->OnHandleStickEnded.AddDynamic(this, &UStickComponent::OnHandleTouchEnded);
	}
	
}

void UStickComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (bProcessing)
	{
		OnStick.Broadcast(LastAxisX, LastAxisY);
	}
	
}

void UStickComponent::OnControllerBorderUpdateVisual()
{
	UTouchBorderBase* BorderBase = GetControllerBorder();
	UTouchStickHandle* StickHandle = Cast<UTouchStickHandle>(GetControllerHandle());
	if (BorderBase && StickHandle)
	{
		StickHandle->InitFirstPosition(BorderBase->GetAdjustedControllerPosition());
	}
}

void UStickComponent::OnHandleTouchBegun(const FVector2D& Location, float AxisX, float AxisY)
{
	LastAxisX = AxisX;
	LastAxisY = AxisY;
	bProcessing = true;
	OnStick.Broadcast(AxisX, AxisY);
}

void UStickComponent::OnHandleTouchMoved(const FVector2D& Location, float AxisX, float AxisY)
{
	LastAxisX = AxisX;
	LastAxisY = AxisY;
}

void UStickComponent::OnHandleTouchEnded(const FVector2D& Location, float AxisX, float AxisY)
{
	LastAxisX = AxisX;
	LastAxisY = AxisY;
	bProcessing = false;
	OnStick.Broadcast(AxisX, AxisY);
}

