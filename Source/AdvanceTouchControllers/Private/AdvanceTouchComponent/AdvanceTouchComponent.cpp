// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "AdvanceTouchComponent/AdvanceTouchComponent.h"

#include "AdvanceTouchComponent/Modules/Border/TouchBorderBase.h"
#include "AdvanceTouchComponent/Modules/Handle/TouchHandleBase.h"
#include "Engine/GameViewportClient.h"

DEFINE_LOG_CATEGORY(AdvanceTouchComponent);

UAdvanceTouchComponent::UAdvanceTouchComponent()
{
	Priority = 0;
	bShowDebug = false;
	
	PrimaryComponentTick.bCanEverTick = false;
}

void UAdvanceTouchComponent::FinishDestroy()
{
	UE_LOG(AdvanceTouchComponent, Log, TEXT("AdvanceTouchComponent runs finishdestroy"))
	Super::FinishDestroy();
}

void UAdvanceTouchComponent::BeginPlay()
{
	Super::BeginPlay();

	// Creates and init border
	ControllerBorder = CreateControllerBorder();
	if (IsValid(ControllerBorder))
	{
		ControllerBorder->SetControllerAlignment(Alignment);
		ControllerBorder->SetControllerOffset(Offset);
		ControllerBorder->SetControllerWidgetClass(BorderWidgetClass);
		ControllerBorder->EnableDebug(bShowDebug);
		ControllerBorder->RunControllerModule();
	}

	// Creates and init handle
	ControllerHandle = CreateControllerHandle();
	if (ControllerHandle)
	{
		ControllerHandle->SetControllerAlignment(Alignment);
		ControllerHandle->SetControllerOffset(Offset);
		ControllerHandle->SetControllerWidgetClass(HandleWidgetClass);
		ControllerHandle->EnableDebug(bShowDebug);
		ControllerHandle->RunControllerModule();
	}
	
}

UTouchBorderBase* UAdvanceTouchComponent::CreateControllerBorder()
{
	if (IsValid(ControllerBorderClass))
	{
		return NewObject<UTouchBorderBase>(this, ControllerBorderClass);
	}
	
	UE_LOG(AdvanceTouchComponent, Error, TEXT("%s does not have control border class"), *this->GetName())
	
	return nullptr;
	
}

UTouchHandleBase* UAdvanceTouchComponent::CreateControllerHandle()
{
	if (IsValid(ControllerHandleClass))
	{
		return NewObject<UTouchHandleBase>(this, ControllerHandleClass);
	}
	
	UE_LOG(AdvanceTouchComponent, Error, TEXT("%s does not have control handle class"), *this->GetName())
	
	return nullptr;
}

void UAdvanceTouchComponent::InputTouch(ETouchIndex::Type FingerIndex, EInputEvent Type,
	const FVector2D& TouchLocation, FDateTime DeviceTimestamp)
{
	if (IsValid(ControllerHandle))
	{
		UE_LOG(AdvanceTouchComponent, Log, TEXT("Priority: %i"), GetPriority());
		UE_LOG(AdvanceTouchComponent, Log, TEXT("Handle finger: %i"), FingerIndex);
		ControllerHandle->InputTouch(Type, TouchLocation, DeviceTimestamp);
	}
}

bool UAdvanceTouchComponent::IsTouchedController(const FVector2D& TouchLocation) const
{
	if (IsValid(ControllerBorder))
	{
		return ControllerBorder->IsTouchInputInBorder(TouchLocation);
	}
	
	UE_LOG(AdvanceTouchComponent, Error, TEXT("%s does not have control border class"), *this->GetName())
	return false;
}

