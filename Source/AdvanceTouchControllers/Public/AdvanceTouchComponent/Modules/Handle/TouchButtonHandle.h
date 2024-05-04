// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "TouchHandleBase.h"
#include "TouchButtonHandle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHandleTouchBegunSignature, FVector2D, TouchLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHandleTouchMovedSignature, FVector2D, TouchLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHandleTouchEndedSignature, FVector2D, TouchLocation);

UCLASS()
class ADVANCETOUCHCONTROLLERS_API UTouchButtonHandle : public UTouchHandleBase
{
	GENERATED_BODY()
	
public:
	FOnHandleTouchBegunSignature OnHandleTouchBegun;
	FOnHandleTouchBegunSignature OnHandleTouchMoved;
	FOnHandleTouchEndedSignature OnHandleTouchEnded;

	void SetButtonSize(const FVector2D& Size){ButtonSize = Size;}


protected:	
	virtual void TouchBegun(const FVector2D& TouchLocation, FDateTime DeviceTimestamp) override;
	virtual void TouchMoved(const FVector2D& TouchLocation, FDateTime DeviceTimestamp) override;
	virtual void TouchEnded(const FVector2D& TouchLocation, FDateTime DeviceTimestamp) override;

	virtual FVector2D GetControllerSize() const override;
	
private:
	// Raw size, it will consider DPI scale
	FVector2D ButtonSize;
};
