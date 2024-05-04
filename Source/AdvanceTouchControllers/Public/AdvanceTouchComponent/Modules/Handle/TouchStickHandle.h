// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "TouchHandleBase.h"
#include "AdvanceTouchComponent/Modules/Border/TouchBorderBase.h"
#include "TouchStickHandle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHandleStickBegunSignature, const FVector2D&, BegunLocation, float, AxisX, float, AxisY)
;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHandleStickMovedSignature, const FVector2D&, ProcessingLocation, float, AxisX, float, AxisY);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHandleStickEndedSignature, const FVector2D&, EndedLocation, float, AxisX, float, AxisY);

UCLASS()
class ADVANCETOUCHCONTROLLERS_API UTouchStickHandle : public UTouchHandleBase
{
	GENERATED_BODY()

protected:
	virtual void TouchBegun(const FVector2D& TouchLocation, FDateTime DeviceTimestamp) override;
	virtual void TouchEnded(const FVector2D& TouchLocation, FDateTime DeviceTimestamp) override;
	virtual void TouchMoved(const FVector2D& TouchLocation, FDateTime DeviceTimestamp) override;
	
	FVector2D GetHandleBorderPosition() const;

	virtual TArray<FVector2D> GetDebugGeometryPoints() override;
	
	void  CalculateAxis(const FVector2D& StartLocation, const FVector2D& EndLocation, float& AxisX, float& AxisY) const;

	virtual FVector2D GetControllerPosition() const override;
	virtual FVector2D GetControllerSize() const override;
	float GetScaledRadius() const;

	virtual void UpdateWidgetProperties() override;

public:
	void InitFirstPosition(const FVector2D& Position);
	FVector2D GetBaseLocation() const;
	
	void SetTouchBorder(UTouchBorderBase* Border);
	void SetEnableUseBorderLocationAsStart(const bool Enable){bUseBorderLocationAsStart = Enable;};
	void SetHandleLength(const float Length){HandleLength = Length;}
	void SetHandleRadius(const float Radius){HandleRadius = Radius;}
	void SetStickBackgroundSize(const FVector2D& Size){StickBackgroundSize = Size;}
	void ClampTouchLocation(FVector2D& TouchLocation);
	
	FOnHandleStickBegunSignature OnHandleStickBegun;
	FOnHandleStickMovedSignature OnHandleStickMoved;
	FOnHandleStickEndedSignature OnHandleStickEnded;

private:
	TWeakObjectPtr<UTouchBorderBase> TouchBorder;
	FVector2D BegunLocation;
	FVector2D LastTouchLocation;
	FVector2D StickBackgroundSize;
	
	bool bUseBorderLocationAsStart;

	float HandleRadius;
	float HandleLength;
};