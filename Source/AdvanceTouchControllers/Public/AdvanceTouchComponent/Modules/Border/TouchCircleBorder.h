// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "TouchBorderBase.h"
#include "TouchCircleBorder.generated.h"

UCLASS()
class ADVANCETOUCHCONTROLLERS_API UTouchCircleBorder : public UTouchBorderBase
{
	GENERATED_BODY()

	UTouchCircleBorder();

public:
	void SetRadius(const float Radius){CircleRadius = Radius;}

protected:
	virtual FVector2D GetControllerSize() const override;
	float GetScaledRadius() const;
	
private:
	virtual bool IsTouchInputInBorder(const FVector2D& TouchLocation) override;
	
	virtual TArray<FVector2D> GetDebugGeometryPoints() override;
	
	// Raw circle radius it will scaled by DPI scale
	UPROPERTY(EditDefaultsOnly, Category="Border")
	float CircleRadius;

	UPROPERTY(EditDefaultsOnly, Category="Border", meta=(EditCondition="bShowDebug", EditConditionHides="true"))
	int32 NumCircleSegments;
};
