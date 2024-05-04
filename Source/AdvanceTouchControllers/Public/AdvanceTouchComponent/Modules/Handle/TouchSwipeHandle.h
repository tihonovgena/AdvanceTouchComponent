// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "TouchHandleBase.h"
#include "TouchSwipeHandle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHandleSwipeUpSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHandleSwipeDownSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHandleSwipeLeftSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHandleSwipeRightSignature);

UCLASS()
class ADVANCETOUCHCONTROLLERS_API UTouchSwipeHandle : public UTouchHandleBase
{
	GENERATED_BODY()

	UTouchSwipeHandle();

protected:
	virtual void TouchBegun(const FVector2D& TouchLocation, FDateTime DeviceTimestamp) override;
	virtual void TouchEnded(const FVector2D& TouchLocation, FDateTime DeviceTimestamp) override;

private:
	float DetectionSwipeTime;
	
	FDateTime TouchBegunDateTime;
	FVector2D BegunLocation;

public:
	void SetDetectionSwipeTime(const float Time){DetectionSwipeTime = Time;}
	
	FOnHandleSwipeUpSignature OnHandleSwipeUp;
	FOnHandleSwipeDownSignature OnHandleSwipeDown;
	FOnHandleSwipeLeftSignature OnHandleSwipeLeft;
	FOnHandleSwipeRightSignature OnHandleSwipeRight;
};
