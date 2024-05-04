// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "TouchHandleBase.h"
#include "TouchTapHandle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHandleTapSignature, FVector2D, TouchLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHandleDoubleTapSignature, FVector2D, TouchLocation);

UCLASS()
class ADVANCETOUCHCONTROLLERS_API UTouchTapHandle : public UTouchHandleBase
{
	GENERATED_BODY()

protected:
	virtual void TouchBegun(const FVector2D& TouchLocation, FDateTime DeviceTimestamp) override;
	virtual void TouchEnded(const FVector2D& TouchLocation, FDateTime DeviceTimestamp) override;

private:
	FDateTime TouchBegunDateTime;
	FDateTime TouchEndedDataTime;
	
	float DetectionTapTime;
	float DetectionDoubleTapTime;
	
	int8 TapAmount;
	
	bool IsSecondTap() const;
	bool DetectDoubleTap(const FDateTime& LastEndTapDate, const FDateTime& CurrentEndTapDate) const;
	
	FTimerHandle TimerHandle;

public:
	void SetDetectionTapTime(const float Time){DetectionTapTime = Time;}
	void SetDetectionDoubleTapTime(const float Time){DetectionDoubleTapTime = Time;}
	
	FOnHandleTapSignature OnTap;
	FOnHandleDoubleTapSignature OnDoubleTap;
};
