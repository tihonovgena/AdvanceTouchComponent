// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "AdvanceTouchComponent/ButtonComponent.h"
#include "AdvanceTouchComponent/Modules/Handle/TouchButtonHandle.h"

UButtonComponent::UButtonComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UButtonComponent::BeginPlay()
{
	Super::BeginPlay();

	UTouchButtonHandle* ButtonHandle = Cast<UTouchButtonHandle>(GetControllerHandle());
	if (ButtonHandle)
	{
		ButtonHandle->OnHandleTouchBegun.AddDynamic(this, &UButtonComponent::OnHandleTouchBegun);
		ButtonHandle->OnHandleTouchEnded.AddDynamic(this, &UButtonComponent::OnHandleTouchEnded);
		ButtonHandle->OnHandleTouchEnded.AddDynamic(this, &UButtonComponent::OnHandleTouchMoved);
	}
	
}

void UButtonComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsPressed)
	{
		OnProcessing.Broadcast(LastTouchPosition);
	}
}

void UButtonComponent::OnHandleTouchBegun(FVector2D TouchLocation)
{
	IsPressed = true;
	SetLastTouchPosition(TouchLocation);
	OnPressed.Broadcast(TouchLocation);
}

void UButtonComponent::OnHandleTouchEnded(FVector2D TouchLocation)
{
	IsPressed = false;
	SetLastTouchPosition(TouchLocation);
	OnReleased.Broadcast(TouchLocation);
}

void UButtonComponent::OnHandleTouchMoved(FVector2D TouchLocation)
{
	SetLastTouchPosition(TouchLocation);
}

